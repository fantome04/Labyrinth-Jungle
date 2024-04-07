#include "coordinate.h"

void Coordinate::change(char dir)
{
	if (dir == 'U')
	{
		first -= 1;
	}
	else if (dir == 'D')
	{
		first += 1;
	}
	else if (dir == 'L')
	{
		second -= 1;
	}
	else if (dir == 'R')
	{
		second += 1;
	}
}



bool operator==(const Coordinate& lhs, const Coordinate& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

bool operator!=(const Coordinate& lhs, const Coordinate& rhs)
{
	return !(lhs == rhs);
}

