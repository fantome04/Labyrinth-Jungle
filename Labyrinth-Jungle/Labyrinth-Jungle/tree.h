#ifndef TREE_H
#define TREE_H

class Tree
{
private:
	Tree(const Coordinate& coord, bool is_grown = false);
	Tree(const Tree& other);
	~Tree() = default;

	void update_tree(); //update tree 4 each instance of the board
	Coordinate get_coordinate() const;
	bool is_grown() const;
	int get_seed_timer() const;
	void set_coordinates(const Coordinate& coord);

private:

	Coordinate location_;
	bool is_grown_;
	int seed_timer_;
	friend bool operator==(const Tree& lhs, const Tree& rhs);
	friend bool operator!=(const Tree& lhs, const Tree& rhs);

};



#endif