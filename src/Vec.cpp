/*
 * Location.cpp
 *
 *  Created on: 18. 11. 2022
 *      Author: lucco
 */

#include <Vec.h>

Vec::Vec() : x(0), y(0)
{
}

Vec::Vec(const Vec &v) : x(v.x), y(v.y)
{
}

Vec::Vec(Vec &&v) : x(v.x), y(v.y)
{
}

Vec::Vec(double x, double y) : x(x), y(y)
{
}

Vec::~Vec()
{
}

Vec& Vec::operator=(const Vec& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

void Vec::set_xy(double x, double y)
{
	this->x = x;
	this->y = y;
}

bool Vec::operator==(const Vec &rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}

bool Vec::operator!=(Vec &rhs)
{
	return (x != rhs.x) || (y != rhs.y);
}

void Vec::set_position(Vec &pos)
{
	x = pos.x;
	y = pos.y;
}

Vec Vec::operator-(Vec &rhs)
{
	return Vec(x - rhs.x, y - rhs.y);
}

Vec Vec::operator+(Vec &rhs)
{
	return Vec(x + rhs.x, y + rhs.y);
}

Vec Vec::operator*(Vec &rhs)
{
	return Vec(x * rhs.x, y * rhs.y);
}

Vec Vec::operator*(double &rhs)
{
	return Vec(x * rhs, y * rhs);
}
