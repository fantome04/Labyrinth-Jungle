#include "lumberjackplayer.h"
#include <iostream>

LumberjackPlayer::LumberjackPlayer(const Coordinate& coord)
	:Player(coord)
	,facing_('U')
	,cuts_left_(3)
{
	my_symbol_ = 'A';
}

bool LumberjackPlayer::move(char input)
{
	if (input == 'w')
	{
		if(facing_ == 'U')
		{
			my_coord_.change('U');
			return true;
		}
		else
		{
			facing_ = 'U';
			my_symbol_ = 'A';
			return false;
		}
	}
	else if (input == 'd')
	{
		if(facing_ == 'R')
		{
			my_coord_.change('R');
			return true;
		}
		else
		{
			facing_ = 'R';
			my_symbol_ = '>';
			return false;
		}
	}
	else if (input == 's')
	{
		if(facing_ == 'D')
		{
			my_coord_.change('D');
			return true;
		}
		else
		{
			facing_ = 'D';
			my_symbol_ = 'V';
			return false;
		}
	}
	else if (input == 'a')
	{
		if(facing_ == 'L')
		{
			my_coord_.change('L');
			return true;
		}
		else
		{
			facing_ = 'L';
			my_symbol_ = '<';
			return false;
		}
	}

	return false;
}

char LumberjackPlayer::facing() const
{
	return facing_;
}


void LumberjackPlayer::cut() 
{
	--cuts_left_;
}

bool LumberjackPlayer::cuts_left() const
{
	return cuts_left_;
}