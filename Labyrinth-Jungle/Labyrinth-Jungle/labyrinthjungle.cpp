#include "labyrinthjungle.h"

LabyrinthJungle::LabyrinthJungle()
	:bfs_called_(false)
{
	generate_labyrinth();
	plant_trees();
	std::cout << "done planting" << std::endl;
	starting_trees();
}

void LabyrinthJungle::update(bool moved)
{
	update_board();
	for (int i = 0; i < number_of_exits_; ++i)
	{
		if (player_coord_ == exits_[i])
		{
			player_on_exit_ = true;
			break;
		}
	}
}

void LabyrinthJungle::update_trees()
{
	for (auto& x : trees_)
	{
		if (!x.is_grown())
		{
			x.update_tree();
		}
	}
}

void LabyrinthJungle::plant_trees()
{
	std::cout << "plant" << std::endl;
	std::vector<std::vector<Coordinate>> path_to_exits(2);
	int count = 0;
	for (int i = 0; i < number_of_exits_; ++i)
	{
		if (!get_path(player_coord_, exits_[i], path_to_exits[i]))
		{
			++count;
		}
	}

	if (count == number_of_exits_)
	{
		path_open_ = false;
		return;
	}

	std::vector<Coordinate> all_free_spaces;
	for (int i = 1; i < board_size_ - 1; ++i)
	{
		for (int j = 1; j < board_size_ - 1; ++j)
		{
			Coordinate temp{ i,j };
			if (!is_tree(temp) && temp != player_coord_)
			{
				all_free_spaces.push_back(temp);
			}
		}
	}

	std::vector<Coordinate> free_no_path;
	for (auto x : all_free_spaces)
	{
		for (int i = 0; i < number_of_exits_; ++i) {
			if (!is_on_path(x, path_to_exits[i]))
			{
				free_no_path.push_back(x);
			}
		}
	}

	std::cout << "random trees finding" << std::endl;

	for (int i = 0; i < 18; ++i)
	{
		Tree tree{ free_no_path[rand() % free_no_path.size()], true };
		trees_.push_back(tree);
		Coordinate temp = tree.get_coordinate();
		all_free_spaces.erase(std::remove(all_free_spaces.begin(), all_free_spaces.end(), temp), all_free_spaces.end());
		free_no_path.erase(std::remove(free_no_path.begin(), free_no_path.end(), temp), free_no_path.end());
	}
	std::cout << "random trees planted" << std::endl;


	for (int i = 0; i < number_of_exits_; ++i) 
	{
		std::vector<Coordinate> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		for (int k = 0; k < directions.size(); ++k)
		{
			int new_row = exits_[i].first + directions[k].first;
			int new_column = exits_[i].second + directions[k].second;

			if (new_row > 0 && new_column > 0 && new_row < board_size_ - 1 && new_column < board_size_ - 1)
			{
				if (board_[new_row][new_column] != TREE)
				{
					std::cout << "found space" << std::endl;
					Tree tr({ new_row, new_column }, true);
					trees_.push_back(tr);
					all_free_spaces.erase(std::remove(all_free_spaces.begin(), all_free_spaces.end(), tr.get_coordinate()), all_free_spaces.end());
					path_to_exits[i].erase(std::remove(path_to_exits[i].begin(), path_to_exits[i].end(), tr.get_coordinate()), path_to_exits[i].end());
					std::cout << "planted space" << std::endl;
				}
			}
		}
		
		std::cout << "found space" << i <<  std::endl;
		Tree tree{ path_to_exits[i][rand() % path_to_exits[i].size()], true };
		trees_.push_back(tree);
		Coordinate temp = tree.get_coordinate();
		all_free_spaces.erase(std::remove(all_free_spaces.begin(), all_free_spaces.end(), temp), all_free_spaces.end());
		path_to_exits[i].erase(std::remove(path_to_exits[i].begin(), path_to_exits[i].end(), temp), path_to_exits[i].end());
		std::cout << "planted space" << i <<  std::endl;
	}

}

bool LabyrinthJungle::cut_tree(const Coordinate& coord, char dir)
{
	Coordinate to_cut = coord;
	to_cut.change(dir);
	if (to_cut.first == 0 || to_cut.second == 0 || to_cut.second == board_size_ - 1 || to_cut.first == board_size_ - 1)
	{
		return false;
	}
	if (board_[to_cut.first][to_cut.second] == TREE)
	{
		board_[coord.first][coord.second] = PATH;
		std::vector<Tree> temp;
		for (auto x : trees_)
		{
			if (x.get_coordinate() != to_cut)
			{
				temp.push_back(x);
			}
		}
		trees_ = temp;
		return true;
	}
	return false;
}

bool LabyrinthJungle::bfs_called() const
{
	return bfs_called_;
}

void LabyrinthJungle::bfs_called_change()
{
	bfs_called_ = true;
}