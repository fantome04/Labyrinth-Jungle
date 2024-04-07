#include "labyrinth.h"
#include <Windows.h>

Labyrinth::Labyrinth()
	:board_(board_size_, std::vector<char>(board_size_, TREE))
	,exits_()
	,trees_()
	,player_coord_()
	,number_of_exits_(0)
	,path_open_(true)
	,player_on_exit_(false)
{
}

void Labyrinth::print()
{
	for (const auto& x : board_)
	{
		for (const auto& y : x)
		{
			std::cout << std::setw(2) << y;
		}
		std::cout << std::endl;
	}
}

void Labyrinth::update(bool moved)
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

bool Labyrinth::get_path(const Coordinate& from, const Coordinate& to, std::vector<Coordinate>& path_to_exit) //bfs
{
	std::vector<std::vector<char>> board_copy(board_size_, std::vector<char>(board_size_, '.'));
	for (auto x : trees_)
	{
		if (x.is_grown())
		{
			board_copy[x.get_coordinate().first][x.get_coordinate().second] = '#';
		}
	}
	board_copy[to.first][to.second] = 'B';
	std::string path = "";
	std::queue<Coordinate> q;
	q.push(from);
	Coordinate b{ -1,-1 };
	while (b.first == -1 && !q.empty())
	{
		auto cell = q.front();
		q.pop();
		int i = cell.first;
		int j = cell.second;


		if (i - 1 >= 0 && (board_copy[i - 1][j] == '.' || board_copy[i - 1][j] == 'B'))
		{
			if (board_copy[i - 1][j] == 'B')
			{
				b.first = i - 1;
				b.second = j;
			}
			q.push({ i - 1, j });
			board_copy[i - 1][j] = 'U';
		}
		if (i + 1 < board_copy.size() && (board_copy[i + 1][j] == '.' || board_copy[i + 1][j] == 'B'))
		{
			if (board_copy[i + 1][j] == 'B')
			{
				b.first = i + 1;
				b.second = j;
			}
			q.push({ i + 1, j });
			board_copy[i + 1][j] = 'D';
		}
		if (j - 1 >= 0 && (board_copy[i][j - 1] == '.' || board_copy[i][j - 1] == 'B'))
		{
			if (board_copy[i][j - 1] == 'B')
			{
				b.first = i;
				b.second = j - 1;
			}
			q.push({ i, j - 1 });
			board_copy[i][j - 1] = 'L';
		}
		if (j + 1 < board_copy[0].size() && (board_copy[i][j + 1] == '.' || board_copy[i][j + 1] == 'B'))
		{
			if (board_copy[i][j + 1] == 'B')
			{
				b.first = i;
				b.second = j + 1;
			}
			q.push({ i, j + 1 });
			board_copy[i][j + 1] = 'R';
		}


	}
	if (b.first != -1)
	{
		Coordinate cur{ b.first, b.second };
		while (!(cur.first == from.first && cur.second == from.second))
		{
			int i = cur.first;
			int j = cur.second;
			path_to_exit.push_back(cur);
			if (board_copy[i][j] == 'U')
			{
				cur.change('D');
			}
			else if (board_copy[i][j] == 'D')
			{
				cur.change('U');
			}
			else if (board_copy[i][j] == 'L')
			{
				cur.change('R');
			}
			else if (board_copy[i][j] == 'R')
			{
				cur.change('L');
			}
		}
		return true;
	}
	return false;
}


std::vector<std::vector<char>> Labyrinth::get_board() const
{
	return board_;
}

std::vector<Coordinate> Labyrinth::get_exits() const
{
	return exits_;
}

void Labyrinth::set_player_coord(const Coordinate& coord)
{
	player_coord_ = coord;
}

void Labyrinth::update_board()
{
	for (int i = 0; i < board_size_; ++i)
	{
		for (int j = 0; j < board_size_; ++j)
		{
			board_[i][j] = '.';
		}
	}
	for (auto x : trees_)
	{
		if (x.is_grown())
		{
			board_[x.get_coordinate().first][x.get_coordinate().second] = '#';
		}
		else
		{
			board_[x.get_coordinate().first][x.get_coordinate().second] = x.get_seed_timer() + '0';
		}
	}
	for (int i = 0; i < number_of_exits_; ++i)
	{
		board_[exits_[i].first][exits_[i].second] = '.';
	}
	board_[player_coord_.first][player_coord_.second] = 'O'; //TODO make actual player symb
}

bool Labyrinth::path_open() const
{
	return path_open_;
}

bool Labyrinth::valid_tree(const Tree& tree, const std::vector<Coordinate>& path)
{
	
	for (auto x : path)
	{
		if (x == tree.get_coordinate())
		{
			std::vector<Coordinate> tmp;
			auto temp = get_path(tree.get_coordinate(), player_coord_, tmp);
			if (!temp)
			{
				std::cout << "wtf" << std::endl;
			}
			else
			{
				if (tmp.size() < tree.get_seed_timer())
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Labyrinth::is_tree(const Coordinate& coord)
{
	for (const auto& x : trees_)
	{
		if (coord == x.get_coordinate())
		{
			return true;
		}
	}
	return false;
}

bool Labyrinth::is_on_path(const Coordinate& coord, const std::vector<Coordinate>& path)
{
	for (const auto& x : path)
	{
		if (coord == x)
		{
			return true;
		}
	}
	return false;
}


