#pragma once
#include "myGeometricObject.h"
#include <vector>

class myBVH : public myGeometricObject
{
public:

	myBVH() {}

	myBVH(std::vector<myGeometricObject*> objects, int AXIS);

	virtual bool hit(const myRay& ray, double& tMin, myShadeRec& sr) const override;

	virtual myRGBColor getColor() const {
		return myRGBColor(1, 1, 1);
	}

	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const override;

	virtual myBBox getBBox() override;

	void create(std::vector<myGeometricObject*> objects, int AXIS);

	virtual ~myBVH() {}

	static int count;

private:
	myGeometricObject* left;
	myGeometricObject* right;
	myBBox bbox;
};