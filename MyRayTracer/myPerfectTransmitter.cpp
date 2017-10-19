#include "myPerfectTransmitter.h"

myRGBColor myPerfectTransmitter::f(const myShadeRec & sr, const myVector & wi, const myVector & wo) const
{
	return myRGBColor();
}

myRGBColor myPerfectTransmitter::sampleF(const myShadeRec & sr, myVector & wi, const myVector & wo) const
{
	myNormal n(sr.normal);
	double cosThetai = dot(n, wo);
	double eta = ior;

	if (cosThetai < 0.0)
	{
		cosThetai = -cosThetai;
		n = -n;
		eta = 1.0 / eta;
	}

	double temp = 1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta);
	double cosTheta2 = sqrtl(temp);
	wi = -wo / eta - myVector((cosTheta2 - cosThetai / eta) * n);

	double ab = dot(sr.normal, wi);
	if (ab < 0.0)
		ab = -ab;
	return myRGBColor(kt / (eta * eta) * 1.0 / ab);
}

myRGBColor myPerfectTransmitter::rho(const myShadeRec & sr, const myVector & wo) const
{
	return myRGBColor();
}

bool myPerfectTransmitter::tir(const myShadeRec & sr) const
{
	myVector wo(-sr.ray.dir);
	double cosThetai = dot(sr.normal , wo);
	double eta = ior;

	if (cosThetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta) < 0.0);
}
