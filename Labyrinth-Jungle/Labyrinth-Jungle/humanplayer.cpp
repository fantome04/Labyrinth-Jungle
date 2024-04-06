#include "humanplayer.h"

#include <stdlib.h>
#include <conio.h>

HumanPlayer::HumanPlayer(const Coordinate& coord)
	:Player(coord)
{
}

//TODO
//Change move
//get_sybmbol
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

char HumanPlayer::get_symbol() const
{
	return my_symbol_;
}

Coordinate HumanPlayer::get_coord() const
{
	return my_coord_;
}


//TODO
//set coord

void HumanPlayer::set_coord(Coordinate coord)
{
	my_coord_ = coord;
}