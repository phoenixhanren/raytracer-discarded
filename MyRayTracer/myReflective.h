#pragma once
#include "myPhong.h"
#include "myPerfectSpecular.h"

class myReflective : public myPhong
{
public:
	myReflective() {}

	myReflective(myLambertian* _ambientBRDF, 
		myLambertian* _diffuseBRDF, 
		myGlossySpecular* _specularBRDF,
		myPerfectSpecular* _reflectiveBRDF) : myPhong(_ambientBRDF, 
			_diffuseBRDF, _specularBRDF), reflectiveBRDF(_reflectiveBRDF) {}

	virtual myRGBColor
		shade(myShadeRec& s) override;

	void setKr(double _kr) {
		reflectiveBRDF->setKr(_kr);
	}

	void setCr(myRGBColor& _cr) {
		reflectiveBRDF->setCr(_cr);
	}

	void setCr(double r, double g, double b) {
		reflectiveBRDF->setCr(r, g, b);
	}

	void setCr(double c) {
		reflectiveBRDF->setCr(c, c, c);
	}



private:
	myPerfectSpecular* reflectiveBRDF;
};