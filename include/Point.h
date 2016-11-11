#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cmath>
struct Point
{
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point() : x(0), y(0) {}
	int x;
	int y;
	friend std::ostream &operator<<(std::ostream& os, Point& point)
	{
		os << "(" << point.x << ", " << point.y << ")";
		return os;
	}
	Point& operator+=(const Point& point)
	{
		x += point.x;
		y += point.y;
		return *this;
	}
	Point& operator/=(const Point& point)
	{
		x /= point.x;
		y /= point.y;
		return *this;
	}
	Point& operator/=(const int size)
	{
		x /= size;
		y /= size;
		return *this;
	}
	double Distance(Point& point)
	{
		return std::sqrt(std::pow(((float)(x - point.x)), 2) + std::pow(((float)(y - point.y)), 2));
	}
};
#endif
