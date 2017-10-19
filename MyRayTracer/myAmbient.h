#pragma once
#include "myLight.h"

class myAmbient : public myLight
{
public:
	myAmbient() : myLight(), ls(1.0), color(1.0) {}

	myAmbient(double _ls, myRGBColor _color) :
		ls(_ls), color(_color) {}

	virtual ~myAmbient() override {}

	virtual myVector
		getDirection(myShadeRec &sr) override;

	virtual myRGBColor
		L(myShadeRec &sr) override;

	void scaleRadiance(double _ls) {
		ls = _ls;
	}

	virtual bool inShadow(const myRay& shadowRay, const myShadeRec &sr) const override {
		return false;
	}

private:
	double ls;
	myRGBColor color;
};