#include "myTransparent.h"
#include "myWorld.h"

myRGBColor myTransparent::shade(myShadeRec & sr)
{
	myRGBColor L(myPhong::shade(sr));

	myVector wo = -sr.ray.dir;
	myVector wi;
	myRGBColor fr = reflectiveBRDF->sampleF(sr, wi, wo);
	myRay reflectedRay(sr.hitPoint, wi);

	if (speculatBTDF->tir(sr))
		L += sr.w.tracerPtr->traceRay(reflectedRay, sr.depth + 1);
	else
	{
		myVector wt;
		myRGBColor ft = speculatBTDF->sampleF(sr, wt, wo);
		myRay transmittedRay(sr.hitPoint, wt);

		double temp = dot(sr.normal, wi);
		if (temp < 0.0)
			temp = -temp;

		double temp2 = dot(sr.normal, wt);
		if (temp2 < 0.0)
			temp2 = -temp2;

		L += fr * sr.w.tracerPtr->traceRay(reflectedRay, sr.depth + 1) * temp;

		L += ft * sr.w.tracerPtr->traceRay(transmittedRay, sr.depth + 1) * temp2;
	} 

	return L;
}
