#pragma once
#include "myLight.h"

class myPointLight : public myLight 
{
public:
	myPointLight() {}

	myPointLight(double _ls, myRGBColor _color, myVector _loc) :
		ls(_ls), color(_color), location(_loc) {}

	virtual 
		~myPointLight() override {}
	
	virtual myVector
		getDirection(myShadeRec& sr) override;

	virtual myRGBColor
		L(myShadeRec& sr) override;

	virtual bool inShadow(const myRay& shadowRay, const myShadeRec &sr) const override;

private:
	double ls;
	myRGBColor color;
	myVector location;
};