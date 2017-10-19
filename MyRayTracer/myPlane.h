#pragma once
#ifndef __myPlane__
#define __myPlane__
#include "myGeometricObject.h"

class myPlane : public myGeometricObject
{
public:
	myPlane() {}
	myPlane(const myPoint &p, const myNormal &n, const myRGBColor &c) :
		point(p), normal(n), color(c) {
		noralize(normal);
	}
	virtual ~myPlane() override {}

	virtual bool hit(const myRay& r, double &tMin, myShadeRec &sr) const override;

	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const override;

	virtual myRGBColor getColor() const override {
		return color;
	}

private:
	myPoint point;
	myNormal normal;
	myRGBColor color;

};
#endif