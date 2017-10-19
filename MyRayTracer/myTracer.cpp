#include "myTracer.h"
#include "myWorld.h"
#include "myShadeRec.h"

myRGBColor myTracer::traceRay(const myRay & ray) const
{
	return myRGBColor(0, 0, 0);
}

myRGBColor myTracer::traceRay(const myRay ray, const int depth) const
{
	return myRGBColor();
}

myRGBColor myTracer::traceRay(const myRay ray, double & tmin, const int depth) const
{
	return myRGBColor();
}

myRGBColor mySingleSphere::traceRay(const myRay & ray) const
{
	myShadeRec sr(*worldPtr);
	double t;

	//if (worldPtr->sphere.hit(ray, t, sr))
	//{
	//	//std::cout << "true : " << t << "\n";
	//	return myRGBColor(1, 0, 0);
	//}
	//	
	//else
	//{
		//std::cout << "false : " << t << "\n";
		return worldPtr->backGroundColor;
	//}
		
}

myRGBColor myMultipleObjects::traceRay(const myRay & ray) const
{
	myShadeRec sr(worldPtr->hitBareBonesObjects(ray));
	if (sr.hitAnObject)
		return sr.color;
	else
		return worldPtr->backGroundColor;
}
