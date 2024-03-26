#include "humanplayer.h"

#include <stdlib.h>
#include <conio.h>

HumanPlayer::HumanPlayer(const Coordinate& coord)
	:Player(coord)
{
}

bool HumanPlayer::move(char dir) //TODO change to Direction class
{

	if (dir == 'U')
	{
		if (facing_ == Direction::UP)
		{
			my_coord_.change('U');
			return true;
		}
		facing_ = Direction::UP;
		return false;
	}
	if (dir == 'R')
	{
		if (facing_ == Direction::RIGHT)
		{
			my_coord_.change('R');
			return true;
		}
		facing_ = Direction::RIGHT;
		return false;
	}
	if (dir == 'D')
	{
		if (facing_ == Direction::DOWN)
		{
			my_coord_.change('D');
			return true;
		}
		facing_ = Direction::DOWN;
		return false;
	}
	if (dir == 'L')
	{
		if (facing_ == Direction::LEFT)
		{
			my_coord_.change('L');
			return true;
		}
		facing_ = Direction::LEFT;
		return false;
	}
	return false;
}



Coordinate HumanPlayer::get_coord() const
{
	return my_coord_;
}


char HumanPlayer::get_symbol()
{
	if (facing_ == Direction::UP)
		return 'A';
	if (facing_ == Direction::DOWN)
		return 'A';
	if (facing_ == Direction::RIGHT)
		return 'A';
	if (facing_ == Direction::LEFT)
		return 'A';
}