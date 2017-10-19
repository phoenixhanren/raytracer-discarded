#pragma once
#include "myTracer.h"

class myWhitted : public myTracer
{
public:
	myWhitted() {}
	myWhitted(myWorld* worldPtr) :
		myTracer(worldPtr) {}

	virtual myRGBColor traceRay(const myRay ray, const int depth) const;
	virtual ~myWhitted() {}
};