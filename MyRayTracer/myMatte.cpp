#include "myMatte.h"
#include "myWorld.h"

myRGBColor myMatte::shade(myShadeRec & sr)
{
	myVector wo = -sr.ray.dir;
	myRGBColor L = ambientBRDF->rho(sr, wo) * sr.w.ambientPtr->L(sr);
	
	for (auto iter = sr.w.lights.cbegin(); iter != sr.w.lights.cend(); ++iter)
	{
		myVector wi = (*iter)->getDirection(sr);
		double ndotwi = dot(myVector(sr.normal.x, sr.normal.y, sr.normal.z),  wi);
		if (ndotwi > 0.0)
			L += diffuseBRDF->f(sr, wo, wi) * (*iter)->L(sr) * ndotwi;
	}

	return L;
}
