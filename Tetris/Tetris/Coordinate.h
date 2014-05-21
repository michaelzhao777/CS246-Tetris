#ifndef __COORDINATE_H__
#define __COORDINATE_H__

struct Coordinate {
	int x, y;
	void set(int x, int y) { this->x = x, this->y = y; }
};

#endif