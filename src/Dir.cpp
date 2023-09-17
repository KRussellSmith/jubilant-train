#include "Dir.hpp"

int Dir::inv(int dir)
{
	switch (dir)
	{
		case Dir::LEFT:
			return Dir::RIGHT;
		case Dir::RIGHT:
			return Dir::LEFT;
		case Dir::UP:
			return Dir::DOWN;
		case Dir::DOWN:
			return Dir::UP;
	}
	return -1;
}