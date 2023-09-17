#include "Touch.hpp"
#include "Dir.hpp"
#include <chrono>
#include <math.h>


double Touch::dist()
{
	double d_x = x - st_x;
	double d_y = y - st_y;
	return sqrt(d_x * d_x + d_y * d_y);
}

void Touch::init(double x, double y)
{
	st_x = x;
	st_y = y;
	this->x = x;
	this->y = y;
	time = 0;
	
	start_time = std::chrono::steady_clock::now();
}
void Touch::move(double x, double y)
{
	this->x = x;
	this->y = y;
	auto curr_time = std::chrono::steady_clock::now();
	time = std::chrono::duration_cast<std::chrono::milliseconds>(curr_time - start_time).count();
}
int Touch::reg_swipe()
{
	auto rel_x = x - st_x;
	auto rel_y = y - st_y;
	if (time < 100 && dist() >= 0.05)
	{
		if (abs(rel_y) < abs(rel_x))
		{
			return rel_x > 0 ? Dir::RIGHT : Dir::LEFT;
		}
		return rel_y > 0 ? Dir::DOWN : Dir::UP;
	}
	return -1;
}

bool Touch::reg_touch()
{
	return time < 100 && dist() < 0.03;
}