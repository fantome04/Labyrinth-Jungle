#include "humanplayer.h"

#include <stdlib.h>
#include <conio.h>

HumanPlayer::HumanPlayer(const Coordinate& coord)
	:Player(coord)
{
}

bool HumanPlayer::move(char dir) //TODO change to Direction class
{
	if (dir == 'w')
	{
		my_coord_.change('U');
	}
	else if (dir == 'd')
	{
		my_coord_.change('R');
	}
	else if (dir == 's')
	{
		my_coord_.change('D');
	}
	else if (dir == 'a')
	{
		my_coord_.change('L');
	}
	else 
	{
		return false;
	}

	return true;
}

char HumanPlayer::facing() const
{
	return 0;
}

bool HumanPlayer::cut()
{
	return false;
}

