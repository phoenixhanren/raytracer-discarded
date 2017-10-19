#pragma once
#include "myLight.h"

class myDirectional : public myLight
{
public:

	myDirectional() {}

	myDirectional(double _ls, myRGBColor _color, myVector _dir) :
		ls(_ls), color(_color), dir(_dir) {
		dir = normalize(dir);
	}

	virtual ~myDirectional() {}

	virtual myVector
		getDirection(myShadeRec &sr) override;

	virtual myRGBColor
		L(myShadeRec &sr) override;

	virtual bool inShadow(const myRay& shadowRay, const myShadeRec &sr) const override;

private:
	double ls;
	myRGBColor color;
	myVector dir;
};