#pragma once
#include "myRGBColor.h"
#include "myShadeRec.h"

class myBTDF
{
public:
	myBTDF() {}

	virtual ~myBTDF() {}

	virtual myRGBColor
		f(const myShadeRec& sr, const myVector& wi, const myVector& wo) const = 0;

	virtual myRGBColor
		sampleF(const myShadeRec& sr, myVector& wi, const myVector& wo) const = 0;

	virtual myRGBColor
		rho(const myShadeRec& sr, const myVector& wo) const = 0;

	virtual bool
		tir(const myShadeRec& sr) const = 0;
};