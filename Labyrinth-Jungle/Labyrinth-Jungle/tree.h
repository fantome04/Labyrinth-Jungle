#ifndef TREE_H
#define TREE_H

#include "coordinate.h"

class Tree
{
public:
	Tree(const Coordinate& coord, bool is_grown = false);
	Tree(const Tree& other);
	~Tree() = default;

	void update_tree(); //reduce timer by 1 if the player moved
	Coordinate get_coordinate() const; // returns tree coordinates
	bool is_grown() const; //returns if the tree is grown
	int get_seed_timer() const; //returns in how many steps the tree will grow
	void set_coordinates(const Coordinate& coord); //set tree coordinates

private:

	Coordinate location_;
	bool is_grown_;
	int seed_timer_;
	friend bool operator==(const Tree& lhs, const Tree& rhs);
	friend bool operator!=(const Tree& lhs, const Tree& rhs);

};



#endif