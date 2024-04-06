#ifndef COORDINATE_H
#define COORDINATE_H

//enum class Direction : char
//{
//	UP = 'U',
//	DOWN = 'D',
//	LEFT = 'L',
//	RIGHT = 'R'
//};

struct Coordinate
{
public:

	void change(char dir); 

	int first;
	int second;

};

bool operator==(const Coordinate& first, const Coordinate& second);
bool operator!=(const Coordinate& first, const Coordinate& second);


#endif