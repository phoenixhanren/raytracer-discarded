#include "myGlossySpecular.h"

myRGBColor myGlossySpecular::f(const myShadeRec & sr, const myVector & wi, const myVector & wo) const
{
    //f(l, wo) = ks * (r * wo) ^ e
	myRGBColor L;
	double ndotwi = dot(myVector(sr.normal), wi);
	myVector r = -wi + myVector(2.0 * sr.normal * ndotwi);
	
	double rdotwo = dot(r, wo);
	if (rdotwo > 0.0)
		L = ks * pow(rdotwo, exp);

	return L;
}

myRGBColor myGlossySpecular::sampleF(const myShadeRec & sr, myVector & wi, const myVector & wo) const
{
	std::cout << "mygloss sampleF" << std::endl;
	return myRGBColor();
}

myRGBColor myGlossySpecular::rho(const myShadeRec & sr, const myVector & wo) const
{
	std::cout << "mygloss rho" << std::endl;
	return myRGBColor();
}
