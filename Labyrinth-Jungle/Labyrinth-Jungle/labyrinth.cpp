#include "labyrinth.h"

Labyrinth::Labyrinth()
	:board_(board_size_, std::vector<char>(board_size_, TREE))
	,player_({ 10, 10 })
	,path_open_(true)
	,player_on_exit_(false)
{
}


void Labyrinth::plant_trees()
{
	std::vector<Coordinate> path_to_exits;
	int count = 0;
	for (int i = 0; i < number_of_exits_; ++i)
	{
		if (!get_path(player_.get_coord(), exits_[i], path_to_exits))
			++count;
		/*for (auto x : path_to_exits)
		{
			std::cout << x.first << " " << x.second << std::endl;
		}*/
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
				all_free_spaces.push_back(temp);
		}
	}

	std::vector<Coordinate> free_no_path;
	for (auto x : all_free_spaces)
	{
		if (!is_on_path(x, path_to_exits))
			free_no_path.push_back(x);

	}
	
	if(free_no_path.size() > 3)
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
	else if(free_no_path.size() == 3)
	{
		for (auto x : free_no_path)
		{
			Tree tree{ x, false };
			trees_.push_back(tree);
		}
	}
}

bool Labyrinth::valid_tree(const Tree& tree, const std::vector<Coordinate>& path)
{
	
	for (auto x : path)
	{
		if (x == tree.get_coordinate())
		{
			std::vector<Coordinate> tmp;
			auto temp = get_path(tree.get_coordinate(), player_.get_coord(), tmp);
			if (!temp)
				std::cout << "wtf" << std::endl;
			else
				if (tmp.size() < tree.get_seed_timer())
					return true;
				else
					return false;
		}
	}

	return true;
}

bool Labyrinth::is_tree(const Coordinate& coord)
{
	for (const auto& x : trees_)
	{
		if (coord == x.get_coordinate())
			return true;
	}
	return false;
}

bool Labyrinth::is_on_path(const Coordinate& coord, const std::vector<Coordinate>& path)
{
	for (auto x : path)
	{
		if (coord == x)
			return true;
	}
	return false;
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
		if(x.is_grown())
			board_[x.get_coordinate().first][x.get_coordinate().second] = '#';
		else
			board_[x.get_coordinate().first][x.get_coordinate().second] = x.get_seed_timer() + '0';
	}
	for (int i = 0; i < number_of_exits_; ++i)
	{
		board_[exits_[i].first][exits_[i].second] = '.';
	}
	board_[player_.get_coord().first][player_.get_coord().second] = player_.get_symbol();
}

void Labyrinth::update_trees()
{
	for (auto& x : trees_)
	{
		if(!x.is_grown())
			x.update_tree();
	}
}

bool Labyrinth::get_path(const Coordinate& from, const Coordinate& to, std::vector<Coordinate>& path_to_exit) //bfs
{
	std::vector<std::vector<char>> board_copy(board_size_, std::vector<char>(board_size_, '.'));
	for (auto x : trees_)
	{
		if (x.is_grown())
			board_copy[x.get_coordinate().first][x.get_coordinate().second] = '#';
	}
	board_copy[to.first][to.second] = 'B';
	std::string path = "";
	std::queue<Coordinate> q;
	q.push(from);
	Coordinate b{ -1,-1 };
	//int bi = -1, bj = -1;
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
			q.push({i - 1, j});
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
			q.push({ i, j - 1});
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
		//int i = b.first, j = b.second;
		while (!(cur.first == from.first && cur.second == from.second))
		{
			int i = cur.first;
			int j = cur.second;
			path_to_exit.push_back(cur);
			if (board_copy[i][j] == 'U')
				cur.change('D');
			else if (board_copy[i][j] == 'D')
				cur.change('U');
			else if (board_copy[i][j] == 'L')
				cur.change('R');
			else if (board_copy[i][j] == 'R')
				cur.change('L');
		}
		return true;
	}
	return false;
}

bool Labyrinth::player_on_exit() const
{
	return player_on_exit_;
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
		if (player_.get_coord() == exits_[i])
		{
			player_on_exit_ = true;
			break;
		}
	}
	
}

Coordinate Labyrinth::get_player_coordinates() const
{
	return player_.get_coord();
}

bool Labyrinth::path_open() const
{
	return path_open_;
}

bool Labyrinth::move_player(char dir)
{
	//TODO
	//move before

	Coordinate before = get_player_coordinates();
	if (player_.move(dir)) {
		Coordinate coord = get_player_coordinates();
		if (board_[coord.first][coord.second] != '#')
			return true;
	}


	player_.set_coord(before);
	return false;
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

