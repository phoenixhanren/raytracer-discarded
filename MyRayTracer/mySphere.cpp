#include "mySphere.h"

bool mySphere::hit(const myRay & ray, double & tMin, myShadeRec & sr) const
{
	double a = dot(ray.dir, ray.dir);
	myVector temp = ray.o - origin;
	double b = dot(2 * temp, ray.dir);
	double c = dot(temp, temp) - radius * radius;

	//double tMin,tMax;
	double t;

	double disc = b * b - 4.0 * a * c;
	if (disc < 0)
		return false;
	else
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;
		if (t > 0.0000001)
		{
			tMin = t;
			myVector tempV = (temp + t * ray.dir) / radius;
			sr.normal = myNormal(tempV.x, tempV.y, tempV.z);
			sr.localHitPoint = ray.o + t * ray.dir;
			return true;
		}
			
		t = (-b + e) / denom;
		if (t > 0.0000001)
		{
			tMin = t;
			myVector tempV = (temp + t * ray.dir) / radius;
			sr.normal = myNormal(tempV.x, tempV.y, tempV.z);
			sr.localHitPoint = ray.o + t * ray.dir;
			return true;
		}
	}
	return false;
}

bool mySphere::shadowHit(const myRay & shadowRay, double & tMin) const
{
	double a = dot(shadowRay.dir, shadowRay.dir);
	myVector temp = shadowRay.o - origin;
	double b = dot(2 * temp, shadowRay.dir);
	double c = dot(temp, temp) - radius * radius;

	//double tMin,tMax;
	double t;

	double disc = b * b - 4.0 * a * c;
	if (disc < 0)
		return false;
	else
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;
		if (t > 0.0000001)
		{
			tMin = t;
			return true;
		}

		t = (-b + e) / denom;
		if (t > 0.0000001)
		{
			tMin = t;
			return true;
		}
	}
	return false;
}
