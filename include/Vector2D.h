#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <cmath>
struct Vector2D
{
	Vector2D(int _x, int _y) : x(_x), y(_y) {}
	Vector2D() : x(0), y(0) {}
	int x;
	int y;
	friend std::ostream &operator<<(std::ostream& os, Vector2D& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ")";
		return os;
	}
	Vector2D& operator+=(const Vector2D& vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}
	Vector2D& operator/=(const Vector2D& vector)
	{
		x /= vector.x;
		y /= vector.y;
		return *this;
	}
	Vector2D& operator/=(const int size)
	{
		x /= size;
		y /= size;
		return *this;
	}
	Vector2D operator*(const Vector2D& vector)
	{
		return Vector2D(x*vector.x, y*vector.y);
	}
	float Magnitude(Vector2D& vector)
	{
		return std::sqrt(std::pow(((float)(x - vector.x)), 2) + std::pow(((float)(y - vector.y)), 2));
	}
	Vector2D Velocity(Vector2D& vector)
	{
		Vector2D velocity;

		return velocity;
	}
};
#endif
