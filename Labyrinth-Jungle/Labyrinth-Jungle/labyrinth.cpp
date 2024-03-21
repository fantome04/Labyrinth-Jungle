#include "labyrinth.h"
#include <vector>
#include <cstdlib>
#include <iostream>


Labyrinth::Labyrinth()
	:board_(board_size_, std::vector<char>(board_size_))
{
	//board generation
	for (int i = 0; i < board_size_; ++i) 
	{
		for (int j = 0; j < board_size_; ++j) 
		{
			int temp = rand() % 2;
			if (temp == 0)
				board_[i][j] = '#';
			else
				board_[i][j] = '.';
		}
	}


	//exits
	number_of_exits_ = rand() % 2 + 1;
	std::vector<int> loc{ 0, 0, 19, 19 };
	for (int i = 0; i < number_of_exits_; ++i)
	{
		int dir = rand() % 4;
		int coord = rand() % 20;

		//  0
		//3   1
		//  2

		if (dir % 2 == 0)
		{
			exits_.push_back({ loc[dir], coord });
			board_[loc[dir]][coord] = 'B';
		}
		else
		{
			exits_.push_back({coord,  loc[dir]});
			board_[coord][loc[dir]] = 'B';
		}
	}

	std::pair<int, int> human_coords{10,10};
	//path guarantee
	for (int i = 0; i < number_of_exits_; ++i)
	{
		std::vector<std::pair<int, int>> path;
		get_path(path, human_coords, exits_[i]);
		for (auto x : path)
		{
			board_[x.first][x.second] = '.';
		}
	}



}

void Labyrinth::get_path(std::vector<std::pair<int, int>>& path, const std::pair<int, int> start, const std::pair<int, int> end)
{
	std::vector<std::vector<char>> board_copy{ board_ };
	std::vector<char> visited;
	dfs(board_copy, visited, start, end, 'O');

	std::pair<int, int> cur{ end };
	while (end != start)
	{
		path.push_back(cur);
		if (board_copy[cur.first][cur.second] == 'U')
			cur.second -= 1;
		else if (board_copy[cur.first][cur.second] == 'D')
			cur.second += 1;
		else if (board_copy[cur.first][cur.second] == 'R')
			cur.first -= 1;
		else if (board_copy[cur.first][cur.second] == 'L')
			cur.first += 1;
	}
}

void Labyrinth::dfs(std::vector<std::vector<char>>& board_copy, std::vector<char>& visited, const std::pair<int, int> start, const std::pair<int, int> end, char prev)
{
	if (start.first < 0 || start.second < 0 || start.first >= board_size_ || start.second >= board_size_ || start == end) {
		return;
	}

	board_copy[start.first][start.second] = prev;

	dfs(board_copy, visited, { start.first + 1, start.second }, end, 'R'); //R
	dfs(board_copy, visited, { start.first - 1, start.second }, end, 'L'); //L
	dfs(board_copy, visited, { start.first, start.second + 1 }, end, 'U'); //U
	dfs(board_copy, visited, { start.first, start.second - 1 }, end, 'D'); //D

}


void Labyrinth::print()
{
	for (auto x : board_)
	{
		for (auto y : x)
		{
			std::cout << y;
		}
		std::cout << std::endl;
	}
}