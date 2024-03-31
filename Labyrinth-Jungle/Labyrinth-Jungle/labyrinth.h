#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <queue>
#include "coordinate.h"
#include "humanplayer.h"
#include "tree.h"
//#include "game.h"
class Game;
class Labyrinth
{
public:
	Labyrinth();

	//probably should be private, don't know hot to make private

private:
	friend class Game;
	
	void print();
	void update(bool moved);
	Coordinate get_player_coordinates() const;
	bool path_open() const;
	bool move_player(char dir);
	void dfs(std::vector<std::vector<char>>& board_, const Coordinate& start);
	int count_visited_neighbours(const std::vector<std::vector<char>>& board_, const Coordinate& start);
	void shuffle(std::vector<int>& visit_order);
	void generate_exits();
	void compare_exits();
	void starting_trees(); //delete later, keep code consistent
	void plant_trees();
	bool valid_tree(const Tree& tree, const std::vector<Coordinate>& path);
	bool is_tree(const Coordinate& coord);
	bool is_on_path(const Coordinate& coord, const std::vector<Coordinate>& path);
	void update_board();
	void update_trees();
	bool get_path(const Coordinate& from, const Coordinate& to, std::vector<Coordinate>& path_to_exit);


	const char TREE = '#';
	const char PATH = '.';

	const int board_size_ = 20;
	std::vector<std::vector<char>> board_;
	int number_of_exits_;
	std::vector<Coordinate> exits_;
	HumanPlayer player_;
	std::vector<Tree> trees_;
	bool path_open_;
	
};

#endif