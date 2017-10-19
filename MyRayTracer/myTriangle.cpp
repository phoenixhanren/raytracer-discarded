#include "myTriangle.h"

bool myTriangle::hit(const myRay & ray, double & tMin, myShadeRec & sr) const
{
	if (hitHelper(ray, tMin))
	{
		sr.normal = normal;
		sr.localHitPoint = ray.o + tMin * ray.dir;
		//std::cout << "hitted" << std::endl;
		return true;
	}
	return false;
}

bool myTriangle::shadowHit(const myRay & shadowRay, double & tMin) const
{
	if (hitHelper(shadowRay, tMin))
	{
		return true;
	}
	return false;
}

myBBox myTriangle::getBBox()
{
	return bbox;
}

void myTriangle::computeNormal()
{
	normal = myNormal(normalize(cross((v2 - v0), (v1 - v0))));
	std::cout << normal << std::endl;
}

bool myTriangle::hitHelper(const myRay& ray, double &tMin) const
{
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.dir.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.dir.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.dir.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j; //
	double q = g * i - e * k, s = e * j - f * i, r1 = e * l - h * i;//

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	//std::cout << beta << std::endl;
	if (beta < 0.0)
		return false;

	double e2 = a * n + d * q + c * r1;
	double gamma = e2 * invDenom;
	if (beta + gamma > 1.0 || gamma < 0.0)
		return false;

	double e3 = a * p + b * (-r1) + d * s;
	double t = e3 * invDenom;

	if (t < KEPSILON)
		return false;

	tMin = t;
	return true;
}
