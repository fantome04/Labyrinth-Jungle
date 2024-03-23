#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player
{
public:

	Player(const Coordinate& coord);

	virtual void move(char dir) = 0; //TODO change to Direction class
	
	virtual char get_symbol() = 0;
	virtual Coordinate get_coord() = 0;

protected:

	Coordinate my_coord_;
	Direction facing_;


};

#endif