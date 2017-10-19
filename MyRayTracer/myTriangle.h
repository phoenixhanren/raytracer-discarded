#pragma once
#include "myGeometricObject.h"

class myTriangle : public myGeometricObject
{
public:

	myTriangle() : v0(0, 0, 0),
		v1(0, 0, 1), v2(1, 0, 0), normal(0, 1, 0) {}

	myTriangle(const myPoint& _v0, const myPoint& _v1, const myPoint& _v2) :
		v0(_v0), v1(_v1), v2(_v2) {
		computeNormal();
		bbox = myBBox(min(min(v0.x, v1.x), v2.x), max(max(v0.x, v1.x), v2.x),
			min(min(v0.y, v1.y), v2.y), max(max(v0.y, v1.y), v2.y),
			min(min(v0.z, v1.z), v2.z), max(max(v0.z, v1.z), v2.z));
		//std::cout << normal << std::endl;
	}

	myTriangle(const myTriangle& rhs) : 
		v0(rhs.v0), v1(rhs.v1), v2(rhs.v2), normal(rhs.normal) {}

	virtual bool hit(const myRay& ray, double& tMin, myShadeRec& sr) const override;

	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const override;

	virtual myBBox getBBox() override;

	virtual myRGBColor getColor() const override {
		return color;
	}

	virtual ~myTriangle() {}

private:

	void computeNormal();
	bool hitHelper(const myRay& ray, double &tMin) const;

	myPoint v0, v1, v2;
	myNormal normal;
	myRGBColor color = myRGBColor(0, 0, 0);
	myBBox bbox;
};