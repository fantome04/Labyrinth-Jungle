#include "player.h"
#include "coordinate.h"

Player::Player(const Coordinate& coord)
	:my_coord_(coord)
	,my_symbol_('X')
{
}

char Player::get_symbol() const
{
	return my_symbol_;
}

Coordinate Player::get_coord() const
{
	return my_coord_;
}

void Player::set_coord(Coordinate coord)
{
	my_coord_ = coord;
}

