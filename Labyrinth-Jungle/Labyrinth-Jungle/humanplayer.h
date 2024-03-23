#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class HumanPlayer : Player
{
public:
	HumanPlayer(const Coordinate& coord);
	virtual void move(char dir) override;
	virtual char get_symbol() override;
	virtual Coordinate get_coord() override;

private:

};

#endif