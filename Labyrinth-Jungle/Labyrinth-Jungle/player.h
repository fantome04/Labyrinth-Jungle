#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player
{
public:

	Player(const Coordinate& coord);

	virtual bool move(char dir) = 0;
	virtual char get_symbol() const;
	virtual Coordinate get_coord() const;
	virtual void set_coord(Coordinate coord);

protected:

	Coordinate my_coord_;
	char my_symbol_;

};

#endif