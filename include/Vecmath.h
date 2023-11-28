/*
 * Vecmath.h
 *
 *  Created on: 3. 12. 2022
 *      Author: lucco
 */

#ifndef INC_VECMATH_H_
#define INC_VECMATH_H_

#include <Vec.h>

#include <cmath>

class Vecmath
{
public:
	enum Compass
	{
		N = 0,
		S = 1,
		W = 2,
		E = 3,
		Unknown
	};

	static double size(Vec &v);
	static void normalize(Vec &v);
	static void set_zero(Vec &v);
	static bool is_zero(Vec &v);
	static Compass get_compass(Vec &v);
	static Vec multiply(Vec &v, double &m);
};

inline double Vecmath::size(Vec &v)
{
	return sqrt((v.x * v.x) + (v.y * v.y));
}

inline void Vecmath::normalize(Vec &v)
{
	auto s = Vecmath::size(v);
	v.set_xy(v.x / s, v.y / s);
}

inline void Vecmath::set_zero(Vec &v)
{
	v.set_xy(0, 0);
}

inline bool Vecmath::is_zero(Vec &v)
{
	return v.x == 0 && v.y == 0;
}

inline Vecmath::Compass Vecmath::get_compass(Vec &v)
{
	if (!Vecmath::is_zero(v))
	{
		if (abs(v.x) > abs(v.y)) /* E or W */
		{
			return v.x > 0 ? Compass::E : Compass::W;
		}
		else /* N or S */
		{
			return v.y > 0 ? Compass::S : Compass::N;
		}
	}
	return Compass::Unknown;
}

inline Vec Vecmath::multiply(Vec &v, double &m)
{
	return Vec(v.x * m, v.y * m);
}

#endif /* INC_VECMATH_H_ */
