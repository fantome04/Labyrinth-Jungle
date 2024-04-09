#include "labyrinthtreeocalypse.h"

LabyrinthTreeocalypse::LabyrinthTreeocalypse()
{
	generate_labyrinth();
	starting_trees();
}

void LabyrinthTreeocalypse::generate_labyrinth()
{
	Coordinate start = { rand() % 18 + 1, rand() % 18 + 1 };
	dfs(start);

	generate_exits();
}

void LabyrinthTreeocalypse::update(bool moved)
{
	if (moved)
	{
		update_trees();
		plant_trees();
	}

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

void LabyrinthTreeocalypse::plant_trees()
{
	std::vector<Coordinate> path_to_exits;
	int count = 0;
	for (int i = 0; i < number_of_exits_; ++i)
	{
		if (!get_path(player_coord_, exits_[i], path_to_exits))
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
			if (!is_tree(temp) || temp != player_coord_)
			{
				all_free_spaces.push_back(temp);
			}
		}
	}

	std::vector<Coordinate> free_no_path;
	for (auto x : all_free_spaces)
	{
		if (!is_on_path(x, path_to_exits))
		{
			free_no_path.push_back(x);
		}

	}

	if (free_no_path.size() > 3)
	{
		for (int i = 0; i < 3; ++i)
		{
			Tree tree{ all_free_spaces[rand() % all_free_spaces.size()], false };
			while (!valid_tree(tree, path_to_exits))
			{
				tree.set_coordinates(all_free_spaces[rand() % all_free_spaces.size()]);
			}
			trees_.push_back(tree);
			Coordinate temp = tree.get_coordinate();
			all_free_spaces.erase(std::remove(all_free_spaces.begin(), all_free_spaces.end(), temp), all_free_spaces.end());
		}
	}
	else if(all_free_spaces.size() > 3)
	{
		std::vector<Tree> temp;
		for (int i = 0; i < 3; ++i)
		{
			Tree tree{ all_free_spaces[rand() % all_free_spaces.size()], false };
			if(valid_tree(tree, path_to_exits))
			{
				temp.push_back(tree);
			}
			else
			{
				temp.clear();
				break;
			}
		}
		for (auto x : temp)
		{
			Coordinate tmp = x.get_coordinate();
			all_free_spaces.erase(std::remove(all_free_spaces.begin(), all_free_spaces.end(), tmp), all_free_spaces.end());
		}
		/*for (auto x : free_no_path)
		{
			Tree tree{ x, false };
			trees_.push_back(tree);
		}*/
	}
}

void LabyrinthTreeocalypse::update_trees()
{
	for (auto& x : trees_)
	{
		if (!x.is_grown())
		{
			x.update_tree();
		}
	}
}



