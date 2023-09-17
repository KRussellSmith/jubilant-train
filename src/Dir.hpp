#ifndef DIR_HPP
#define DIR_HPP

typedef struct
{
	int x, y;
} Coord;

const Coord DIR[4] = {
	{-1,  0}, // left
	{ 1,  0}, // right
	{ 0, -1}, // up
	{ 0,  1}  // down
};

namespace Dir
{
	enum
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
	int inv(int dir);
}
#endif