#pragma once
#include "myMaterial.h"
#include "myLambertian.h"

class myMatte : public myMaterial
{
public:
	myMatte() : 
	ambientBRDF(new myLambertian), diffuseBRDF(new myLambertian) {}

	myMatte(const myMatte &rhs) :
	ambientBRDF(rhs.ambientBRDF), diffuseBRDF(rhs.diffuseBRDF) {}

	myMatte(myLambertian* _ambientBRDF, myLambertian* _diffuseBRDF) :
		ambientBRDF(_ambientBRDF), diffuseBRDF(_diffuseBRDF) {}

	void setKA(const double k) {
		ambientBRDF->setKD(k);
	}

	void setKD(const double k) {
		diffuseBRDF->setKD(k);
	}

	void setCD(const myRGBColor& c) {
		diffuseBRDF->setCD(c);
		diffuseBRDF->setCD(c);
	}

	virtual myRGBColor shade(myShadeRec &sr) override;



private:
	myLambertian* ambientBRDF;
	myLambertian* diffuseBRDF;
};