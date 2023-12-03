/*
 * Location.h
 *
 *  Created on: 18. 11. 2022
 *      Author: lucco
 */

#ifndef INC_VEC_H_
#define INC_VEC_H_

#include <cmath>

class Vec
{
public:
	Vec();
	Vec(const Vec &v);
	Vec(Vec &&v);
	Vec(double x, double y);
	virtual ~Vec();
    Vec &operator=(const Vec &v);
    void set_xy(double x, double y);
    void set_position(Vec &pos);
	bool operator==(const Vec &rhs) const;
	bool operator!=(Vec &rhs);
	Vec operator-(Vec &rhs);
	Vec operator+(Vec &rhs);
	Vec operator*(Vec &rhs);
	Vec operator*(double &rhs);
	double x;
	double y;
};

#endif /* INC_VEC_H_ */
