#include "myAmbient.h"

myVector myAmbient::getDirection(myShadeRec & sr)
{
	return myVector(0.0, 0.0, 0.0);
}

myRGBColor myAmbient::L(myShadeRec & sr)
{
	return ls * color;
}
