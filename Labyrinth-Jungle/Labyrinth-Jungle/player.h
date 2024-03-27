#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:

	Player(const Coordinate& coord);

	virtual bool move(char dir) = 0; //TODO change to Direction class
	
	virtual char get_symbol() = 0;
	virtual Coordinate get_coord() const = 0;

protected:

	Coordinate my_coord_;
	Direction facing_;

};

#endif