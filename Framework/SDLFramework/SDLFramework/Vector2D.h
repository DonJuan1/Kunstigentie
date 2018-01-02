#pragma once
#include <math.h>
#include <iostream>

struct Vector2D
{
	double x;
	double y;

	Vector2D() :x(0.0), y(0.0)
	{}
	Vector2D(double a, double b) :x(a), y(b)
	{}

	inline double Distance(const Vector2D &v2)const;

	inline double DistanceSq(const Vector2D &v2)const;

	const Vector2D& operator+=(const Vector2D &rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	const Vector2D& operator-=(const Vector2D &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	const Vector2D& operator*=(const double& rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	const Vector2D& operator/=(const double& rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	bool operator!=(const Vector2D& rhs)const
	{
		return (x != rhs.x) || (y != rhs.y);
	}

};

inline Vector2D operator*(const Vector2D &lhs, double rhs);
inline Vector2D operator*(double lhs, const Vector2D &rhs);
inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs);
inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs);
inline Vector2D operator/(const Vector2D &lhs, double val);

inline double Vector2D::Distance(const Vector2D &v2)const
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;

	return sqrt(ySeparation*ySeparation + xSeparation * xSeparation);
}

inline double Vector2D::DistanceSq(const Vector2D &v2)const
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;

	return ySeparation * ySeparation + xSeparation * xSeparation;
}

inline double Vec2DDistance(const Vector2D &v1, const Vector2D &v2)
{

	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;

	return sqrt(ySeparation*ySeparation + xSeparation * xSeparation);
}

inline double Vec2DDistanceSq(const Vector2D &v1, const Vector2D &v2)
{

	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;

	return ySeparation * ySeparation + xSeparation * xSeparation;
}

inline Vector2D operator*(const Vector2D &lhs, double rhs)
{
	Vector2D result(lhs);
	result *= rhs;
	return result;
}

inline Vector2D operator*(double lhs, const Vector2D &rhs)
{
	Vector2D result(rhs);
	result *= lhs;
	return result;
}

inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;

	return result;
}

inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D result(lhs);
	result.x += rhs.x;
	result.y += rhs.y;

	return result;
}

inline Vector2D operator/(const Vector2D &lhs, double val)
{
	Vector2D result(lhs);
	result.x /= val;
	result.y /= val;

	return result;
}
