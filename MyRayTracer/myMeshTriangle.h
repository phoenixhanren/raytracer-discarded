#pragma once

#include <vector>
#include "myGeometricObject.h"
#include "myMesh.h"

class myMesh;

class myMeshTriangle : public myGeometricObject
{
	
public:

	myMeshTriangle() {
		computeNormal();
		computeBBox();
	}

	myMeshTriangle(myMesh *_meshPtr, int _index0, int _index1, int _index2) : 
		meshPtr(_meshPtr), index0(_index0), index1(_index1), index2(_index2)	{
		computeNormal();
		computeBBox();
	}

	virtual ~myMeshTriangle() {}

	virtual bool hit(const myRay& ray, double& tMin, myShadeRec& sr) const override;
	
	virtual myRGBColor getColor() const override {
		return color;
	};

	myNormal getNormal() {
		return normal;
	}

	virtual bool shadowHit(const myRay& shadowRay, double &tMin) const override;

	virtual myBBox getBBox() override;

	int index0, index1, index2;

private:
	myNormal interpolateNormal(const double beta, const double gamma) const;

	bool hitHelper(const myRay& ray, double &tMin, myNormal &normal) const;

	void computeBBox();

	void computeNormal();

	myMesh *meshPtr;


	myNormal normal;

	myRGBColor color = myRGBColor(0, 0, 0);

	myBBox bbox;

};

std::ostream& operator<<(std::ostream& os, myMeshTriangle& mesh);