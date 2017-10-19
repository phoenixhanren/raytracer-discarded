#pragma once
#include "myMaterial.h"
#include "myLambertian.h"
#include "myGlossySpecular.h"

class myPhong : public myMaterial
{
public:
	myPhong() {}

	myPhong(myPhong& rhs) : ambientBRDF(rhs.ambientBRDF),
		diffuseBRDF(rhs.ambientBRDF),
		specularBRDF(rhs.specularBRDF) {}

	myPhong(myLambertian* _ambientBRDF, myLambertian* _diffuseBRDF, myGlossySpecular* _specularBRDF) :
		ambientBRDF(_ambientBRDF), diffuseBRDF(_diffuseBRDF), specularBRDF(_specularBRDF) {}

	virtual myRGBColor
		shade(myShadeRec& s) override;

protected:
	myLambertian* ambientBRDF;
	myLambertian* diffuseBRDF;
	myGlossySpecular* specularBRDF;
};