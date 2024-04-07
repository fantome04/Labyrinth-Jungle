#ifndef COORDINATE_H
#define COORDINATE_H

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