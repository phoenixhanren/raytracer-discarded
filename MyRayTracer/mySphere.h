#pragma once
#ifndef __mySphere__
#define __mySphere__
#include "myGeometricObject.h"

class mySphere : public myGeometricObject
{
public:
	mySphere() {}
	mySphere(const myPoint& o, double r,const myRGBColor &c) :
		origin(o), radius(r), color(c) {
		computeBBox();
	}

	mySphere(const myPoint& o, double r) :
		mySphere(o, r, myRGBColor(1, 1, 1)) {
		computeBBox();
	}

	virtual ~mySphere() override {}

	virtual bool hit(const myRay& ray, double& tMin, myShadeRec& sr) const override;
	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const override;
	virtual myRGBColor getColor() const override {
		return color;
	}
	bool setColor(const myRGBColor &c) {
		color = c;
	}

	virtual myBBox getBBox() {
		return bbox;
	}

	double radius;
	myPoint origin;
	myRGBColor color = myRGBColor(0, 0, 0);
	myBBox bbox;

private:
	void computeBBox() {
		bbox = myBBox(origin.x - radius, origin.x + radius,
			origin.y - radius, origin.y + radius,
			origin.z - radius, origin.z + radius);
	}
};
#endif