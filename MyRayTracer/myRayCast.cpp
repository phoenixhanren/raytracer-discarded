#include "myRayCast.h"
#include "myWorld.h"
#include "myShadeRec.h"

myRGBColor myRayCast::traceRay(const myRay & ray) const
{
	myShadeRec sr(worldPtr->hitObjects(ray));

	if (sr.hitAnObject)
	{
		sr.ray = ray;
			
		return sr.materialPtr->shade(sr);
	}
	else
		return worldPtr->backGroundColor;
}

myRGBColor myRayCast::traceRay(const myRay ray, const int depth) const
{
	myShadeRec sr(worldPtr->hitObjects(ray));

	if (sr.hitAnObject)
	{
		sr.ray = ray;
		return sr.materialPtr->shade(sr);
	}
	else
		return worldPtr->backGroundColor;
}
