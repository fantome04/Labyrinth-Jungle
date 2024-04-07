#include "labyrinthtreeocalypse.h"

LabyrinthTreeocalypse::LabyrinthTreeocalypse()
{
	generate_labyrinth();
}

void LabyrinthTreeocalypse::generate_labyrinth()
{
	Coordinate start = { rand() % 18 + 1, rand() % 18 + 1 };
	dfs(board_, start);

	generate_exits();
	starting_trees();
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
			if (!is_tree(temp))
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
	else if (free_no_path.size() == 3)
	{
		for (auto x : free_no_path)
		{
			Tree tree{ x, false };
			trees_.push_back(tree);
		}
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


void LabyrinthTreeocalypse::dfs(std::vector<std::vector<char>>& board_, const Coordinate& start)
{
	if (count_visited_neighbours(board_, start) > 1)
	{
		return;
	}

	board_[start.first][start.second] = PATH;

	std::vector<Coordinate> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	std::vector<int> visit_order = { 0, 1, 2, 3 };

	shuffle(visit_order);

	for (int i = 0; i < directions.size(); ++i)
	{
		int new_row = start.first + directions[visit_order[i]].first;
		int new_column = start.second + directions[visit_order[i]].second;

		if (new_row >= 1 && new_column >= 1 && new_row < board_size_ - 1 && new_column < board_size_ - 1)
		{
			if (board_[new_row][new_column] == TREE)
			{
				dfs(board_, { new_row, new_column });
			}
		}
	}
}

int LabyrinthTreeocalypse::count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start)
{
	int count = 0;
	std::vector<Coordinate> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	for (int i = 0; i < directions.size(); ++i)
	{
		int new_row = start.first + directions[i].first;
		int new_column = start.second + directions[i].second;

		if (new_row >= 1 && new_column >= 1 && new_row < board_size_ - 1 && new_column < board_size_ - 1)
		{
			if (board_[new_row][new_column] == PATH)
			{
				++count;
			}
		}
	}

	return count;
}

void LabyrinthTreeocalypse::shuffle(std::vector<int>& visit_order) {
	int size = visit_order.size();

	for (int i = 0; i < size; ++i)
	{
		std::swap(visit_order[i], visit_order[rand() % size]);
	}
}

void LabyrinthTreeocalypse::generate_exits()
{
	number_of_exits_ = rand() % 2 + 1;
	std::vector<int> loc{ 0, 0, 19, 19 };
	for (int i = 0; i < number_of_exits_; ++i)
	{
		int dir = rand() % 4;
		int coord = rand() % 18 + 1;

		//  0
		//1   3
		//  2

		if (dir % 2 == 0)
		{
			while ((loc[dir] == 0 && board_[1][coord] == TREE) || (loc[dir] == 19 && board_[18][coord] == TREE))
			{
				coord = rand() % 18 + 1;
			}

			exits_.push_back({ loc[dir], coord });
		}
		else
		{
			while ((loc[dir] == 0 && board_[coord][1] == TREE) || (loc[dir] == 19 && board_[coord][18] == TREE))
			{
				coord = rand() % 18 + 1;
			}

			exits_.push_back({ coord,  loc[dir] });
		}
	}

	if (number_of_exits_ == 2)
	{
		compare_exits();
	}

	for (int i = 0; i < number_of_exits_; ++i) {
		board_[exits_[i].first][exits_[i].second] = PATH;
	}
}

void LabyrinthTreeocalypse::compare_exits()
{
	if (exits_[0].first == exits_[1].first)
	{
		if ((exits_[0].second + 1 == exits_[1].second) || (exits_[0].second - 1 == exits_[1].second))
		{
			exits_.pop_back();
			--number_of_exits_;
		}
	}

	else if (exits_[0].second == exits_[1].second)
	{
		if ((exits_[0].first + 1 == exits_[1].first) || (exits_[0].first - 1 == exits_[1].first))
		{
			exits_.pop_back();
			--number_of_exits_;
		}
	}
}

void LabyrinthTreeocalypse::starting_trees()
{
	for (int i = 0; i < board_size_; ++i)
	{
		for (int j = 0; j < board_size_; ++j)
		{
			if (board_[i][j] == '#')
			{
				trees_.push_back(Tree({ i, j }, true));
			}
		}
	}
}


