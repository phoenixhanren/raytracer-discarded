#pragma once

#include "myBRDF.h"

class myGlossySpecular : public myBRDF
{
public:
	myGlossySpecular() : exp(0.0), ks(0.0) {}

	myGlossySpecular(double _exp, double _ks) :
		exp(_exp), ks(_ks) {}

	virtual ~myGlossySpecular() {}

	virtual myRGBColor
		f(const myShadeRec& sr, const myVector& wi, const myVector& wo) const override;

	virtual myRGBColor
		sampleF(const myShadeRec& sr, myVector& wi, const myVector& wo) const override;

	virtual myRGBColor
		rho(const myShadeRec& sr, const myVector& wo) const override;

	void setExp(double _exp) {
		exp = _exp;
	}

	void setKs(double _ks) {
		ks = _ks;
	}

private:
	double exp;
	double ks;

};