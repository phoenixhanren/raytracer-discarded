#pragma once
#include "myMath.h"

class myBBox
{
public:
	double x0, x1, y0, y1, z0, z1;

	myBBox() : x0(INFINITY), x1(-INFINITY),
		y0(INFINITY), y1(-INFINITY),
		z0(INFINITY), z1(-INFINITY)
	{}

	myBBox(double _x0, double _x1, double _y0, double _y1,
		double _z0, double _z1) :
		x0(_x0), x1(_x1), y0(_y0), y1(_y1), z0(_z0), z1(_z1) {}

	bool hit(const myRay& ray) const;
};

myBBox combine(const myBBox& left, const myBBox& right);