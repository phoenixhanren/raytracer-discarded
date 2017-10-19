#pragma once
#include "myTracer.h"
class myRayCast : public myTracer
{
public:
	myRayCast() {};
	myRayCast(myWorld* worldPtr) :
		myTracer(worldPtr) {}

	virtual myRGBColor 
		traceRay(const myRay& ray) const override;

	virtual myRGBColor
		traceRay(const myRay ray, const int depth) const override;

	virtual
		~myRayCast() override {};
};