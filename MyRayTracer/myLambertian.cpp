#include "myLambertian.h"

myRGBColor myLambertian::f(const myShadeRec & sr, const myVector & wi, const myVector & wo) const
{
	return (cd * INV_PI * kd);
}

myRGBColor myLambertian::sampleF(const myShadeRec & sr, myVector & wi, const myVector & wo) const
{
	return myRGBColor();
}

myRGBColor myLambertian::rho(const myShadeRec & sr, const myVector & wo) const
{
	return cd * kd;
}
