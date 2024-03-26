#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include "coordinate.h"

class Labyrinth
{
public:

	Labyrinth();

	void print();

private:
	
	void dfs(std::vector<std::vector<char>>& board_, const Coordinate& start);
	int count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start);
	void shuffle(std::vector<int>& visit_order);
	void generate_exits();
	void compare_exits();

	const char TREE = '#';
	const char PATH = '.';

	const int board_size_ = 20;
	std::vector<std::vector<char>> board_;
	int number_of_exits_;
	std::vector<Coordinate> exits_;
};

#endif