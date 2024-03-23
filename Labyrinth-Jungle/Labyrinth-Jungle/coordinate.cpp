#include "coordinate.h"

void Coordinate::move(char dir)
{
	if (dir == 'U')
		first -= 1;
	else if (dir == 'D')
		first += 1;
	else if (dir == 'L')
		second -= 1;
	else if (dir == 'R')
		second += 1;
}
