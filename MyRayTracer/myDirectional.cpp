#include "myDirectional.h"

myVector myDirectional::getDirection(myShadeRec & sr)
{
	return dir;
}

myRGBColor myDirectional::L(myShadeRec & sr)
{
	return ls * color;
}

bool myDirectional::inShadow(const myRay & shadowRay, const myShadeRec & sr) const
{
	return false;
}
