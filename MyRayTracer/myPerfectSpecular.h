#pragma once
#include "myBRDF.h"

class myPerfectSpecular : public myBRDF
{
public:
	myPerfectSpecular() {}

	virtual ~myPerfectSpecular() {}

	virtual myRGBColor
		f(const myShadeRec& sr, const myVector& wi, const myVector& wo) const;

	virtual myRGBColor
		sampleF(const myShadeRec& sr, myVector& wi, const myVector& wo) const override;

	virtual myRGBColor
		rho(const myShadeRec& sr, const myVector& wo) const;

	void setKr(double _kr) {
		kr = _kr;
	}

	void setCr(myRGBColor& _cr) {
		cr = _cr;
	}

	void setCr(double r, double g, double b) {
		cr = myRGBColor(r, g, b);
	}

	void setCr(double c) {
		setCr(c, c, c);
	}


private:
	double kr; //reflection coefficient
	myRGBColor cr; //the reflection color
};