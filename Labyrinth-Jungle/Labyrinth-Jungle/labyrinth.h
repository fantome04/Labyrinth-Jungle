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

class Labyrinth
{
public:

	Labyrinth();
	virtual ~Labyrinth() = default;
	
	virtual void print();
	virtual void update(bool moved);
	virtual Coordinate get_player_coordinates() const;
	virtual bool path_open() const;
	virtual bool move_player(char dir);
	
	virtual void generate_labyrinth() = 0;


	virtual void plant_trees() = 0;
	
	virtual bool valid_tree(const Tree& tree, const std::vector<Coordinate>& path);
	virtual bool is_tree(const Coordinate& coord);
	virtual bool is_on_path(const Coordinate& coord, const std::vector<Coordinate>& path);
	virtual void update_board();
	virtual void update_trees();
	virtual bool get_path(const Coordinate& from, const Coordinate& to, std::vector<Coordinate>& path_to_exit); //bfs
	virtual bool player_on_exit() const;

protected:

	const char TREE = '#';
	const char PATH = '.';

	const int board_size_ = 20;
	std::vector<std::vector<char>> board_;
	int number_of_exits_;
	std::vector<Coordinate> exits_;
	HumanPlayer player_;
	std::vector<Tree> trees_;
	bool path_open_;
	bool player_on_exit_;
	
};

#endif