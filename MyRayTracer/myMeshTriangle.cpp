#include "myMeshTriangle.h"

bool myMeshTriangle::hit(const myRay & ray, double & tMin, myShadeRec & sr) const
{
	myNormal temp;
	if (hitHelper(ray, tMin, temp))
	{
		sr.normal = temp;
		sr.localHitPoint = ray.o + tMin * ray.dir;
		return true;
	}
	return false;
}

bool myMeshTriangle::shadowHit(const myRay & shadowRay, double & tMin) const
{
	myNormal temp;
	if (hitHelper(shadowRay, tMin, temp))
	{
		return true;
	}
	return false;
}

myBBox myMeshTriangle::getBBox()
{
	return bbox;
}

myNormal myMeshTriangle::interpolateNormal(const double beta, const double gamma) const
{
	myNormal temp = (1 - beta - gamma) * meshPtr->normals[index0] +
		beta * meshPtr->normals[index1] + gamma * meshPtr->normals[index2];
	return noralize(temp);
}

bool myMeshTriangle::hitHelper(const myRay & ray, double & tMin, myNormal &normal) const
{
	myPoint v0 = meshPtr->vertices[index0];
	myPoint v1 = meshPtr->vertices[index1];
	myPoint v2 = meshPtr->vertices[index2];

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
	normal = interpolateNormal(beta, gamma);
	//normal = this->normal;
	return true;
}

void myMeshTriangle::computeBBox()
{
	double delta = 0.0000000001;
	double x0 = INFINITY, x1 = -INFINITY, y0 = INFINITY,
		y1 = -INFINITY, z0 = INFINITY, z1 = -INFINITY;
	myPoint p1 = meshPtr->vertices[index0];
	myPoint p2 = meshPtr->vertices[index1];
	myPoint p3 = meshPtr->vertices[index2];
	x0 = min(x0, min(min(p1.x, p2.x), p3.x) - delta);
	y0 = min(y0, min(min(p1.y, p2.y), p3.y) - delta);
	z0 = min(z0, min(min(p1.z, p2.z), p3.z) - delta);
	x1 = max(x1, max(max(p1.x, p2.x), p3.x) + delta);
	y1 = max(y1, max(max(p1.y, p2.y), p3.y) + delta);
	z1 = max(z1, max(max(p1.z, p2.z), p3.z) + delta);
	//std::cout << x0 << " " << x1 << " " << y0 << " " << y1
	//	<< " " << z0 << " " << z1 << std::endl;
	bbox = myBBox(x0, x1, y0, y1, z0, z1);
}

void myMeshTriangle::computeNormal()
{
	myPoint v0 = meshPtr->vertices[index0];
	myPoint v1 = meshPtr->vertices[index1];
	myPoint v2 = meshPtr->vertices[index2];
	normal = myNormal(normalize(cross((v1 - v0), (v2 - v0))));
}

std::ostream& operator<<(std::ostream& os, myMeshTriangle& mesh) {
	auto temp = mesh.getNormal();
	os << temp.x << " " << temp.y << " " << temp.z << "\n";
	return os;
}