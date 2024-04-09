#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(const Coordinate& coord);
	virtual bool move(char dir) override;
	
private:

};

#endif