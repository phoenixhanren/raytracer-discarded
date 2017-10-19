#include "myPerfectSpecular.h"

myRGBColor myPerfectSpecular::f(const myShadeRec & sr, const myVector & wi, const myVector & wo) const
{
	return myRGBColor();
}

myRGBColor myPerfectSpecular::sampleF(const myShadeRec & sr, myVector & wi, const myVector & wo) const
{
	double ndotwo = dot(sr.normal, wo);
	wi = -wo + myVector(2.0 *sr.normal * ndotwo);

	return kr * cr / fabs((dot(sr.normal, wi)));
}



myRGBColor myPerfectSpecular::rho(const myShadeRec & sr, const myVector & wo) const
{
	return myRGBColor();
}
