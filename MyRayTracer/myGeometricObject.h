#pragma once
#ifndef __myGeometricObject__
#define __myGeometricObject__
#include "myMath.h"
#include "myShadeRec.h"
#include "myMaterial.h"
#include "myBBox.h"

class myGeometricObject
{
public:
	myGeometricObject() {}

	virtual bool hit(const myRay& ray, double& tMin, myShadeRec& sr) const = 0;
	virtual myRGBColor getColor() const = 0;

	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const = 0;

	virtual myBBox getBBox() {
		return myBBox();
	}

	virtual ~myGeometricObject() {}

	myMaterial* getMaterial() { return materialPtr; }
	void setMaterial(myMaterial* mM) { materialPtr = mM; }

private:
	myMaterial* materialPtr;

};
#endif