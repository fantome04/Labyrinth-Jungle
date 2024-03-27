#include "labyrinth.h"

Labyrinth::Labyrinth()
	:board_(board_size_, std::vector<char>(board_size_, TREE))
	,player_({10,10})
{
	Coordinate start = { 1, 1 };
	dfs(board_, start);

	generate_exits();
	starting_trees();
}

void Labyrinth::dfs(std::vector<std::vector<char>>& board_, const Coordinate& start)
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

int Labyrinth::count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start)
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

void Labyrinth::shuffle(std::vector<int>& visit_order) {
	int size = visit_order.size();

	for (int i = 0; i < size; ++i)
	{
		std::swap(visit_order[i], visit_order[rand() % size]);
	}
}

void Labyrinth::generate_exits()
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

	board_[player_.get_coord().first][player_.get_coord().second] = 'O';
}

void Labyrinth::compare_exits()
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

void Labyrinth::starting_trees()
{
	for (int i = 0; i < board_size_; ++i)
	{
		for (int j = 0; j < board_size_; ++j)
		{
			if (board_[i][j] == '#')
				trees_.push_back(Tree({ i,j }, true));
		}
	}
}

void Labyrinth::plant_trees()
{
	std::vector<Coordinate> free_spaces;
	for (int i = 0; i < board_size_; ++i)
	{
		for (int j = 0; j < board_size_; ++j)
		{
			if (board_[i][j] == '.')
				free_spaces.push_back({ i,j });
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		Tree tree{ free_spaces[rand() % free_spaces.size()], false };
		while (!valid_tree(tree))
		{
			tree.set_coordinates(free_spaces[rand() % free_spaces.size()]);
		}
		trees_.push_back(tree);
	}
}

bool Labyrinth::valid_tree(const Tree& tree)
{
	//TODO 
	return true;
}

void Labyrinth::update_board()
{
	for (int i = 0; i < board_size_; ++i)
	{
		for (int j = 0; j < board_size_; ++j)
		{
			if (std::find(trees_.begin(), trees_.end(), Tree{ {i,j},false }) != trees_.end())
			{
				board_[i][j] == '#';
			}
			else
			{
				board_[i][j] == '.';
			}

		}
	}
	for (int i = 0; i < number_of_exits_; ++i)
	{
		board_[exits_[i].first][exits_[i].second] == '.';
	}
	board_[player_.get_coord().first][player_.get_coord().second] = player_.get_symbol();
}

void Labyrinth::update(bool moved)
{
	if (moved)
		plant_trees();
	update_board();
	
}

Coordinate Labyrinth::get_player_coordinates() const
{
	return player_.get_coord();
}

bool Labyrinth::move_player(char dir)
{
	//TODO check wall collision
	player_.move(dir);
	return true;
}

void Labyrinth::print()
{
	for (auto x : board_)
	{
		for (auto y : x)
		{
			std::cout << std::setw(2) << y;
		}
		std::cout << std::endl;
	}
}

