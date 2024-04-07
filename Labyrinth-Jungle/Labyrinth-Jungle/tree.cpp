#include "tree.h"
#include "coordinate.h"
#include <cstdlib>

Tree::Tree(const Coordinate& coord, bool is_grown)
	:location_(coord)
	,is_grown_(is_grown)
	,seed_timer_(0)
{
	if (!is_grown)
	{
		seed_timer_ = rand() % 10 + 1;
	}
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
	{
		--seed_timer_;
	}
	else
	{
		is_grown_ = true;
	}
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

void Tree::set_coordinates(const Coordinate& coord)
{
	location_ = coord;
}

bool operator==(const Tree& lhs, const Tree& rhs)
{
	return lhs.location_ == rhs.location_ && lhs.is_grown_ == rhs.is_grown_ && lhs.seed_timer_ == rhs.seed_timer_;
}

bool operator!=(const Tree& lhs, const Tree& rhs)
{
	return !(lhs == rhs);
}
