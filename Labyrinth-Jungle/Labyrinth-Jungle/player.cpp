#include "player.h"

Player::Player(const Coordinate& coord)
	:my_coord_(coord)
	,facing_(Direction::UP)
{
}

