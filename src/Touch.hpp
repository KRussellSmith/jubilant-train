#ifndef TOUCH_HPP
#define TOUCH_HPP
#include <chrono>

class Touch
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start_time;
public:
	double x;
	double y;
	double st_x;
	double st_y;
	
	int time;
	
	double dist();
	
	void init(double x, double y);
	void move(double x, double y);
	
	int  reg_swipe();
	bool reg_touch();
};
#endif