#ifndef LUMBERJACKPLAYER_H
#define LUMBERJACKPLAYER_H

#include "player.h"

class LumberjackPlayer : public Player
{
public:
	LumberjackPlayer(const Coordinate& coord);

	virtual bool move(char input) override;

	char facing() const;


	void cut();
	int cuts_left() const;
	
private:

	char facing_;
	int cuts_left_;

};


#endif // !LUMBERJACKPLAYER_H
