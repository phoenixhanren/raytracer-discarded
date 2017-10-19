#include "myPlane.h"

bool myPlane::hit(const myRay &r, double & tMin, myShadeRec & sr) const
{
	tMin = dot((point - r.o), normal) / dot(r.dir, normal);

	if (tMin < r.tMin || tMin > r.tMax)
		return false;
	sr.normal = normal;
	sr.localHitPoint = r.o + tMin * r.dir;
	return true;
}

bool myPlane::shadowHit(const myRay & shadowRay, double & tMin) const
{
	tMin = dot((point - shadowRay.o), normal) / dot(shadowRay.dir, normal);

	if (tMin < shadowRay.tMin || tMin > shadowRay.tMax || tMin < KEPSILON)
		return false;
	return true;

}
