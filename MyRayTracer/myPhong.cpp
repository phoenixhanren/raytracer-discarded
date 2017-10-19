#include "myPhong.h"
#include "myWorld.h"

myRGBColor myPhong::shade(myShadeRec & s)
{
	myVector wo = -s.ray.dir;
	myRGBColor L = ambientBRDF->rho(s, wo) * s.w.ambientPtr->L(s);
	
	for (auto iter = s.w.lights.cbegin(); iter != s.w.lights.cend(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			myVector wi = (*iter)->getDirection(s);
			double ndotwi = dot(myVector(s.normal), wi);

			if (ndotwi > 0.0)
			{
				bool inShadow = false;

				myRay shadowRay = myRay(s.hitPoint, wi);
				inShadow = (*iter)->inShadow(shadowRay, s);

				if (!inShadow)
				{
					L += (diffuseBRDF->f(s, wo, wi) +
						specularBRDF->f(s, wo, wi)) * (*iter)->L(s) * ndotwi;
				}

			}
		}
	}
	return L;
}
