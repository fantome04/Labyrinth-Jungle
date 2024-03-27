#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class HumanPlayer : Player
{
public:
	HumanPlayer(const Coordinate& coord);
	virtual bool move(char dir) override;
	virtual char get_symbol() override;
	virtual Coordinate get_coord() const override;

private:

};

#endif