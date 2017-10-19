#include "myRectangle.h"

bool myRectangle::hit(const myRay & ray, double & tMin, myShadeRec & sr) const
{
	double t = dot((p0 - ray.o),  normal) / dot(ray.dir , normal);

	if (t <= KEPSILON)
		return false;

	myPoint p = ray.o + t * ray.dir;
	myVector d = p - p0;

	double ddota = dot(d , a);

	if (ddota < 0.0 || ddota > aLengthSquared)
		return false;

	double ddotb = dot(d , b);

	if (ddotb < 0.0 || ddotb > bLengthSquared)
		return (false);

	tMin = t;
	sr.normal = normal;
	sr.localHitPoint = p;

	return true;
}

bool myRectangle::shadowHit(const myRay & shadowRay, double & tMin) const
{
	double t = dot((p0 - shadowRay.o), normal) / dot(shadowRay.dir, normal);

	if (t <= KEPSILON)
		return false;

	myPoint p = shadowRay.o + t * shadowRay.dir;
	myVector d = p - p0;

	double ddota = dot(d, a);

	if (ddota < 0.0 || ddota > aLengthSquared)
		return false;

	double ddotb = dot(d, b);

	if (ddotb < 0.0 || ddotb > bLengthSquared)
		return (false);

	tMin = t;


	return true;
}

myBBox myRectangle::getBBox()
{
	return bbox;
}
