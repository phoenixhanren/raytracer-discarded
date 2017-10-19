#pragma once
class myWorld;
#include "myRGBColor.h"
#include "myMath.h"

class myTracer
{
public:
	myTracer() {}
	myTracer(myWorld* wPtr): worldPtr(wPtr) {}

	virtual myRGBColor traceRay(const myRay& ray) const;
	virtual myRGBColor traceRay(const myRay ray, const int depth) const;
	virtual myRGBColor traceRay(const myRay ray, double &tmin, const int depth) const;

	virtual ~myTracer() {}

protected:
	myWorld* worldPtr;
};

class mySingleSphere : public myTracer
{
public:
	mySingleSphere(myWorld* wPtr) : myTracer::myTracer(wPtr) {}
	virtual myRGBColor traceRay(const myRay& ray) const override;

};

class myMultipleObjects : public myTracer
{
public:
	myMultipleObjects(myWorld* wPtr) : myTracer::myTracer(wPtr) {}
	virtual myRGBColor traceRay(const myRay& ray) const override;
};