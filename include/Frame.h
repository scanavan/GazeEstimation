#ifndef FRAME_H
#define FRAME_H
#include <iostream>
#include <cmath>
struct Frame
{
	Frame(float _x, float _y, long _time_ms) : x(_x), y(_y), time_ms(_time_ms) {}
	Frame() : x(0.f), y(0.f), time_ms(0.l) {}
	float x;
	float y;
  long time_ms;

	float Magnitude(Frame& frame)
	{
		return std::sqrt(std::pow(((float)(x - frame.x)), 2) + std::pow(((float)(y - frame.y)), 2));
	}

	float Velocity_overall(Frame& frame)
	{
		return Magnitude(frame)/ static_cast<float>(frame.time_ms - time_ms);
	}
};
#endif
