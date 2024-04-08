#ifndef LUMBERJACKPLAYER_H
#define LUMBERJACKPLAYER_H

#include "player.h"

class LumberjackPlayer : public Player
{
public:
	LumberjackPlayer(const Coordinate& coord);

	virtual bool move(char input) override;
	//virtual char get_symbol() const override;

	char facing() const;


	bool cut();
	//void stop_cutting();
	
private:

	char facing_;
	//bool cutting_;
	int cuts_left_;

};


#endif // !LUMBERJACKPLAYER_H
