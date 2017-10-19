#pragma once
#include "myGeometricObject.h"
#include "myPlyHelper.h"
#include "myBBox.h"
#include "myMaterial.h"

class myBoundMeshTriangle : public myGeometricObject
{
public:

	myBoundMeshTriangle() {}

	myBoundMeshTriangle(char *fileName, myMaterial* material);

	virtual bool hit(const myRay& ray, double& tMin, myShadeRec& sr) const override;
	virtual myRGBColor getColor() const override {
		return myRGBColor(0, 0, 0);
	};

	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const override;

	virtual ~myBoundMeshTriangle() {
		if (mesh != nullptr)
			delete mesh;
		for (auto iter = triangles.begin(); iter != triangles.end(); ++iter)
		{
			if ((*iter) != nullptr)
			{
				delete (*iter);
			}
		}
	}

private:


	myMesh *mesh;
	std::vector<myMeshTriangle*> triangles;
	myBBox bbox;

};