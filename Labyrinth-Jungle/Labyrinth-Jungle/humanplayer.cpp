#include "humanplayer.h"

#include <stdlib.h>
#include <conio.h>

HumanPlayer::HumanPlayer(const Coordinate& coord)
	:Player(coord)
{
}

void HumanPlayer::move(char dir) //TODO change to Direction class
{
	/*char press = ' ';
	if (_kbhit())
		press = _getch();
	switch (press)
	{
	case 'w':
		my_coord_.change('U');
		break;
	case 'd':
		my_coord_.change('R');
		break;
	case 's':
		my_coord_.change('D');
		break;
	case 'a':
		my_coord_.change('L');
		break;
	default:
		break;
	}*/

	if (dir == 'U')
	{
		if (facing_ == Direction::UP)
			my_coord_.change('U');
		else
			facing_ = Direction::UP;
	}
	else if (dir == 'R')
	{
		if (facing_ == Direction::RIGHT)
			my_coord_.change('R');
		else
			facing_ = Direction::RIGHT;
	}
	else if (dir == 'D')
	{
		if (facing_ == Direction::DOWN)
			my_coord_.change('D');
		else
			facing_ = Direction::DOWN;
	}
	else if (dir == 'L')
	{
		if (facing_ == Direction::LEFT)
			my_coord_.change('L');
		else
			facing_ = Direction::LEFT;
	}
}



Coordinate HumanPlayer::get_coord()
{
	return my_coord_;
}


char HumanPlayer::get_symbol()
{
	if (facing_ == Direction::UP)
		return 'A';
	if (facing_ == Direction::DOWN)
		return 'V';
	if (facing_ == Direction::RIGHT)
		return '>';
	if (facing_ == Direction::LEFT)
		return '<';
}