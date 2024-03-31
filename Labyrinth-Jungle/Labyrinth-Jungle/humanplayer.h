#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class HumanPlayer : Player
{
public:
	HumanPlayer(const Coordinate& coord);
	virtual bool move(char dir) override;
	virtual char get_symbol() const override;
	virtual Coordinate get_coord() const override;
	virtual void set_coord(Coordinate coord) override;

private:

};

#endif