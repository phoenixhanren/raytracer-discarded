#pragma once

#include "mySampler.h"
#include "myRGBColor.h"
#include "myShadeRec.h"

class myBRDF
{
public:
	myBRDF() {}

	virtual ~myBRDF() {}

	virtual myRGBColor
		f(const myShadeRec& sr, const myVector& wi, const myVector& wo) const = 0;

	virtual myRGBColor
		sampleF(const myShadeRec& sr, myVector& wi, const myVector& wo) const = 0;

	virtual myRGBColor
		rho(const myShadeRec& sr, const myVector& wo) const = 0;

protected:
	mySampler* samplerPtr;
};