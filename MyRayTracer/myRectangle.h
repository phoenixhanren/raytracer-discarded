#pragma once
#include "myGeometricObject.h"

class myRectangle : public myGeometricObject
{
public:
	myRectangle() : myGeometricObject(),
	p0(-1, 0, -1), a(0, 0, 2), b(2, 0, 0),
	aLengthSquared(4.0), bLengthSquared(4.0),
	normal(0, 1, 0) {}

	myRectangle(const myPoint& _p0, const myVector& _a,
		const myVector& _b) : p0(_p0), a(_a), b(_b),
		aLengthSquared(_a.lengthSquared()), bLengthSquared(
	_b.lengthSquared()){
		std::cout << a << b;
		normal = noralize(myNormal(cross(a, b)));
		std::cout << normal;
	}

	virtual bool hit(const myRay& ray, double& tMin, myShadeRec& sr) const override;

	virtual myRGBColor getColor() const override {
		return myRGBColor(0, 0, 0);
	}

	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const override;

	virtual myBBox getBBox() override;
	

	virtual ~myRectangle() {}

private:
	void computeBBox() {
		double delta = 0.0001;

		bbox = (myBBox(min(p0.x, p0.x + a.x + b.x) - delta, max(p0.x, p0.x + a.x + b.x) + delta,
			min(p0.y, p0.y + a.y + b.y) - delta, max(p0.y, p0.y + a.y + b.y) + delta,
			min(p0.z, p0.z + a.z + b.z) - delta, max(p0.z, p0.z + a.z + b.z) + delta));
	}
	myPoint p0; //corner vertex
	myVector a; //side
	myVector b; //side
	double aLengthSquared;
	double bLengthSquared;
	myNormal normal;
	myBBox bbox;
};