#include "tree.h"

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
