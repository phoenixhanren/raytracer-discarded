#pragma once
#include "myBRDF.h"

class myLambertian : public myBRDF
{
public:
	myLambertian() {}

	myLambertian(double _kd, myRGBColor _cd) :
		kd(_kd), cd(_cd) {}

	virtual ~myLambertian() override {}

	virtual myRGBColor
		f(const myShadeRec& sr, const myVector& wi, const myVector& wo) const override;

	virtual myRGBColor
		sampleF(const myShadeRec& sr,myVector& wi, const myVector& wo) const override;

	virtual myRGBColor
		rho(const myShadeRec& sr, const myVector& wo) const override;
		
	void setKD(double _kd) {
		kd = _kd;
	}

	void setCD(myRGBColor _cd) {
		cd = _cd;
	}

private:
	double kd;
	myRGBColor cd;
};