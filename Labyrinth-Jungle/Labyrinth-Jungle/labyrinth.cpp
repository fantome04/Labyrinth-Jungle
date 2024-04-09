#include "labyrinth.h"

#include <Windows.h>

Labyrinth::Labyrinth()
	:board_(board_size_, std::vector<char>(board_size_, TREE))
	,exits_()
	,trees_()
	,player_coord_()
	,player_symb_('X')
	,number_of_exits_(0)
	,path_open_(true)
	,player_on_exit_(false)
{
}

void Labyrinth::print()
{
	std::cout << "\n\n\n";
	for (const auto& x : board_)
	{
		std::cout << "\t\t\t";
		for (const auto& y : x)
		{
			if (y == TREE )
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | FOREGROUND_GREEN);
			}
			else if (y == SEED)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			}
			else if (y == PATH)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);;
			}
			std::cout << std::setw(2) << y;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		std::cout << std::endl;
	}
}

void Labyrinth::generate_labyrinth()
{
	Coordinate start = { rand() % 18 + 1, rand() % 18 + 1 };
	dfs(start);

	generate_exits();
	std::cout << "generate" << std::endl;
}

bool Labyrinth::get_path(const Coordinate& from, const Coordinate& to, std::vector<Coordinate>& path_to_exit) const //bfs
{
	std::vector<std::vector<char>> board_copy(board_size_, std::vector<char>(board_size_, PATH));
	for (const auto& x : trees_)
	{
		if (x.is_grown())
		{
			board_copy[x.get_coordinate().first][x.get_coordinate().second] = TREE;
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


		if (i - 1 >= 0 && (board_copy[i - 1][j] == PATH || board_copy[i - 1][j] == 'B'))
		{
			if (board_copy[i - 1][j] == 'B')
			{
				b.first = i - 1;
				b.second = j;
			}
			q.push({ i - 1, j });
			board_copy[i - 1][j] = 'U';
		}
		if (i + 1 < board_copy.size() && (board_copy[i + 1][j] == PATH || board_copy[i + 1][j] == 'B'))
		{
			if (board_copy[i + 1][j] == 'B')
			{
				b.first = i + 1;
				b.second = j;
			}
			q.push({ i + 1, j });
			board_copy[i + 1][j] = 'D';
		}
		if (j - 1 >= 0 && (board_copy[i][j - 1] == PATH || board_copy[i][j - 1] == 'B'))
		{
			if (board_copy[i][j - 1] == 'B')
			{
				b.first = i;
				b.second = j - 1;
			}
			q.push({ i, j - 1 });
			board_copy[i][j - 1] = 'L';
		}
		if (j + 1 < board_copy[0].size() && (board_copy[i][j + 1] == PATH || board_copy[i][j + 1] == 'B'))
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

std::vector<Tree> Labyrinth::get_trees() const
{
	return trees_;
}

std::vector<Coordinate> Labyrinth::get_exits() const
{
	return exits_;
}

void Labyrinth::set_player_coord(const Coordinate& coord)
{
	player_coord_ = coord;
}

void Labyrinth::set_player_symbol(char symb)
{
	player_symb_ = symb;
}

void Labyrinth::update_board()
{
	for (int i = 0; i < board_size_; ++i)
	{
		for (int j = 0; j < board_size_; ++j)
		{
			board_[i][j] = PATH;
		}
	}
	for (const auto& x : trees_)
	{
		if (x.is_grown())
		{
			board_[x.get_coordinate().first][x.get_coordinate().second] = TREE;
		}
		else
		{
			//board_[x.get_coordinate().first][x.get_coordinate().second] = x.get_seed_timer() + '0';
			board_[x.get_coordinate().first][x.get_coordinate().second] = SEED;
		}
	}
	for (int i = 0; i < number_of_exits_; ++i)
	{
		board_[exits_[i].first][exits_[i].second] = PATH;
	}
	board_[player_coord_.first][player_coord_.second] = player_symb_; 
}

bool Labyrinth::path_open() const
{
	return path_open_;
}

bool Labyrinth::valid_tree(const Tree& tree, const std::vector<Coordinate>& path)
{
	
	for (const auto& x : path)
	{
		if (x == tree.get_coordinate())
		{
			std::vector<Coordinate> tmp;
			auto temp = get_path(tree.get_coordinate(), player_coord_, tmp);
			return tmp.size() < tree.get_seed_timer();
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

void Labyrinth::dfs(const Coordinate& start)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	print();
	if (count_visited_neighbours(start) > 1)
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
				dfs({ new_row, new_column });
			}
		}
	}
}

int Labyrinth::count_visited_neighbours(const Coordinate& start)
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


	for (int i = 0; i < number_of_exits_; ++i) 
	{
		board_[exits_[i].first][exits_[i].second] = PATH;
	}
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
			if (board_[i][j] == TREE)
			{
				trees_.push_back(Tree({ i, j }, true));
			}
		}
	}
}

char Labyrinth::get_tree_symb() const
{
	return TREE;
}

char Labyrinth::get_path_symb() const
{
	return PATH;
}

char Labyrinth::get_seed_symb() const
{
	return SEED;
}