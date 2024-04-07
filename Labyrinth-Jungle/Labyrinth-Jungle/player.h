#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player
{
public:

	Player(const Coordinate& coord);

	virtual bool move(char dir) = 0; //TODO change to Direction class
	virtual char get_symbol() const = 0;
	virtual Coordinate get_coord() const = 0;
	virtual void set_coord(Coordinate coord) = 0;

protected:

	Coordinate my_coord_;

	const char my_symbol_ = 'O';

};

#endif