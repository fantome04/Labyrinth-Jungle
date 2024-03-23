#include "tree.h"
#include "coordinate.h"

Tree::Tree(const Coordinate& coord, bool is_grown)
	:location_(coord)
	,is_grown_(is_grown)
	,seed_timer_(0)
{
	if (!is_grown)
		seed_timer_ = rand() % 10 + 1;
}

Tree::Tree(const Tree& other)
	:location_(other.location_)
	,is_grown_(other.is_grown_)
	,seed_timer_(other.seed_timer_)
{
}

void Tree::update_tree()
{
	if (seed_timer_ > 0)
		--seed_timer_;
	else
		is_grown_ = true;
}

Coordinate Tree::get_coordinate() const
{
	return location_;
}

bool Tree::is_grown() const
{
	return is_grown_;
}

int Tree::get_seed_timer() const
{
	return seed_timer_;
}

