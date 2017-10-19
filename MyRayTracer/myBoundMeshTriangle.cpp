#include "myBoundMeshTriangle.h"

myBoundMeshTriangle::myBoundMeshTriangle(char * fileName, myMaterial *material)
{
	mesh = new myMesh;
	readPly(fileName, mesh, triangles, myMatrix(1, 1, 1, 's'), myMatrix(1, 1, 1, 's'));
	computeMeshNormal(mesh, triangles);
	double x0 = INFINITY, x1 = -INFINITY, y0 = INFINITY,
		y1 = -INFINITY, z0 = INFINITY, z1 = -INFINITY;
	double delta = 0.0000001;
	for (auto iter = triangles.begin(); iter != triangles.end(); ++iter)
	{
		(*iter)->setMaterial(material);
		//(*iter)->index0
		myPoint p1 = mesh->vertices[(*iter)->index0];
		myPoint p2 = mesh->vertices[(*iter)->index1];
		myPoint p3 = mesh->vertices[(*iter)->index2];
		x0 = min(x0, min(min(p1.x, p2.x), p3.x) - delta);
		y0 = min(y0, min(min(p1.y, p2.y), p3.y) - delta);
		z0 = min(z0, min(min(p1.z, p2.z), p3.z) - delta);
		x1 = max(x1, max(max(p1.x, p2.x), p3.x) + delta);
		y1 = max(y1, max(max(p1.y, p2.y), p3.y) + delta);
		z1 = max(z1, max(max(p1.z, p2.z), p3.z) + delta);
	}
	bbox = myBBox(x0, x1, y0, y1, z0, z1);
	setMaterial(material);
}

bool myBoundMeshTriangle::hit(const myRay & ray, double & tMin, myShadeRec & sr) const
{

	if (!bbox.hit(ray))
	{
		//std::cout << false;
		return false;
	}
	//std::cout << 233 << std::endl;
	
	tMin = INFINITY;
	double t;
	myNormal normal;
	myPoint localHitPoint;
	for (auto iter = triangles.cbegin(); iter != triangles.cend(); ++iter)
	{
		if (*iter == nullptr)
			continue;

		if ((*iter)->hit(ray, t, sr) && (t < tMin))
		{
			//std::cout << bbox.hit(ray) << std::endl;
			sr.hitAnObject = true;
			tMin = t;
			sr.materialPtr = (*iter)->getMaterial();
			
			sr.hitPoint = ray.o + t * ray.dir;

			normal = sr.normal;
			localHitPoint = sr.localHitPoint;
		}
	}
	if (sr.hitAnObject)
	{
		sr.t = tMin;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
		return true;
	}
	//std::cout << bbox.hit(ray) << std::endl;
	return false;
}

bool myBoundMeshTriangle::shadowHit(const myRay & shadowRay, double & tMin) const
{
	if (!bbox.hit(shadowRay))
	{
		return false;
	}
	
	for (auto iter = triangles.cbegin(); iter != triangles.cend(); ++iter)
	{
		if (*iter == nullptr)
			continue;

		if ((*iter)->shadowHit(shadowRay, tMin))
		{
			return true;
		}
	}
	return false;

}
