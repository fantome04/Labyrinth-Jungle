#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include "coordinate.h"
#include "humanplayer.h"
//#include "game.h"

class Labyrinth
{
public:

	Labyrinth();

	//probably should be private, don't know hot to make private
	void print();
	void update(const Coordinate& prev);
	Coordinate get_player_coordinates() const;
	bool move_player(char dir);

private:
	//friend class Game;
	
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
	HumanPlayer player_;
	//Player* player_; //2 class lini mardkanc hamar, pointer-ov pahac lini, kaxvac mode-ic chisht tesaki playery new arvi
};

#endif