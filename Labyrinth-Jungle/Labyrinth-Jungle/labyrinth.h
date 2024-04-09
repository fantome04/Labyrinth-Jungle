#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <ranges>
#include <queue>
#include "coordinate.h"
#include "humanplayer.h"
#include "tree.h"

class Labyrinth
{
public:

	Labyrinth();
	virtual ~Labyrinth() = default;

	virtual void print(); //print board
	virtual void update(bool moved) = 0; //update everything

	virtual void generate_labyrinth();
	virtual void plant_trees() = 0;
	virtual void update_trees() = 0;

	// Bfs algorithm with backtracking
	// Bfs starts on coordinate from, ends on coordinate to
	// Return a vector of coordinates of the path from 'from' to 'to
	// The vector is not guaranteed to be in the actual order of the path, it just stores the coordinates
	// the function is written in a way that it can be called multiple times and 'path to exit' can hold coordinates for multiple paths
	virtual bool get_path(const Coordinate& from, const Coordinate& to, std::vector<Coordinate>& path_to_exit);

	virtual std::vector<std::vector<char>> get_board() const; //returns a copy of the board
	virtual std::vector<Tree> get_trees() const; //returns a copy of the trees vector
	virtual std::vector<Coordinate> get_exits() const; //returns a copy of the vector of exit coordinates
	virtual void set_player_coord(const Coordinate& coord); //tells the labyrinth where the player is
	virtual void set_player_symbol(char symb);

	virtual void update_board(); //update board
	virtual bool path_open() const; //returns if the path to the exit from the players location is open
	virtual bool valid_tree(const Tree& tree, const std::vector<Coordinate>& path); //returns if the planted tree can exit on given path(s)
	virtual bool is_tree(const Coordinate& coord); //returns if there is a tree on given coordinate
	virtual bool is_on_path(const Coordinate& coord, const std::vector<Coordinate>& path); //returns if the coordinate is a part of given path(s)

	

protected:

	void dfs(const Coordinate& start); //generate labyrinth with dfs
	int count_visited_neighbours(const Coordinate& start); //helper function
	void shuffle(std::vector<int>& visit_order); //helper function
	void generate_exits(); //generates exit(s) on board
	void compare_exits(); //compares exit locations with each other
	void starting_trees(); //creates vector of trees at the start of the game

	const char TREE = '#';
	const char PATH = '.';
	const int board_size_ = 20;

	std::vector<std::vector<char>> board_;
	std::vector<Coordinate> exits_;
	std::vector<Tree> trees_;

	Coordinate player_coord_;
	char player_symb_;

	int number_of_exits_;

	bool path_open_;
	bool player_on_exit_;
	
};

#endif