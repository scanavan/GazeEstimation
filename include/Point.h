#ifndef POINT_H
#define POINT_H
struct Point
{
	Point(float _x, float _y) : x(_x), y(_y) {}
	Point() : x(0.f), y(0.f) {}
	float x;
	float y;
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
	Point& operator/=(const size_t size)
	{
		x /= size;
		y /= size;
		return *this;
	}
	float Distance(Point& point)
	{
		return std::sqrt(std::pow((x - point.x), 2.f) + std::pow((y - point.y), 2.f));
	}
};
#endif
