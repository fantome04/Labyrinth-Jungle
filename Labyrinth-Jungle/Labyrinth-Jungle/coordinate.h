#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:

	Coordinate(int i, int j);
	Coordinate(const Coordinate& other);
	~Coordinate() = default;

	int first() const;
	int second() const;
	void move(char dir); //might have a better way to implement
						 //directions might be better handled with an enum class

private:

	int i_; //names are subject to change
	int j_;

};

#endif