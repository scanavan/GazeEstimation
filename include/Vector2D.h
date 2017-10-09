#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>
#include <cmath>
struct Vector2D
{
	Vector2D(float _x, float _y) : x(_x), y(_y) {}
	Vector2D() : x(0.f), y(0.f) {}
	float x;
	float y;
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
	float Velocity_overall(Vector2D& vector, long time_frame)
	{
		return Magnitude(vector)/ time_frame;
	}

	Vector2D Velocity_points( const Vector2D& vector, long time_frame )
	{
		return Vector2D(std::abs(vector.x - x)/ time_frame , std::abs(vector.y - y) / time_frame);
	}

};
#endif
