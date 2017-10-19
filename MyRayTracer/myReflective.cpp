#include "myReflective.h"
#include "myWorld.h"

myRGBColor myReflective::shade(myShadeRec & s)
{
	myRGBColor L(myPhong::shade(s));

	myVector wo = -s.ray.dir;
	myVector wi;
	myRGBColor fr = reflectiveBRDF->sampleF(s, wi, wo);
	myRay reflectedRay(s.hitPoint, wi);
	

	L += fr * s.w.tracerPtr->traceRay(reflectedRay, s.depth + 1) * (dot(s.normal, wi));

	return L;
}
