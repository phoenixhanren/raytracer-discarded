#pragma once
#include "myShadeRec.h"
#include "myRGBColor.h"

class myLight
{
public:

	myLight() {}

	virtual ~myLight() {}

	virtual myVector
		getDirection(myShadeRec &sr) = 0;

	virtual myRGBColor
		L(myShadeRec &sr) = 0;

	virtual bool inShadow(const myRay& shadowRay, const myShadeRec &sr) const = 0;

protected:
	bool shadows;
};