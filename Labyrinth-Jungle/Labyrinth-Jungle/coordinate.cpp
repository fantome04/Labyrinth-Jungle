#include "coordinate.h"

Coordinate::Coordinate(int i, int j)
	:i_(i)
	,j_(j)
{
}

Coordinate::Coordinate(const Coordinate& other)
	:i_(other.i_)
	,j_(other.j_)
{
}

int Coordinate::first() const
{
	return i_;
}

int Coordinate::second() const
{
	return j_;
}

void Coordinate::move(char dir)
{
	if (dir == 'U')
		i_ -= i_;
	else if (dir == 'D')
		i_ += 1;
	else if (dir == 'L')
		j_ -= 1;
	else if (dir == 'R')
		j_ += 1;
}
