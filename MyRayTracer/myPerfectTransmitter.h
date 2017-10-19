#pragma once
#include "myBTDF.h"

class myPerfectTransmitter : public myBTDF
{
public:
	myPerfectTransmitter() {}

	myPerfectTransmitter(double _ior, double _kt) :
		ior(_ior), kt(_kt) {}

	virtual ~myPerfectTransmitter() {}

	virtual myRGBColor
		f(const myShadeRec& sr, const myVector& wi, const myVector& wo) const override;

	virtual myRGBColor
		sampleF(const myShadeRec& sr, myVector& wi, const myVector& wo) const override;

	virtual myRGBColor
		rho(const myShadeRec& sr, const myVector& wo) const override;

	virtual bool
		tir(const myShadeRec& sr) const override;

private:
	double ior;
	double kt;
};