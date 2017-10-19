#include "myPointLight.h"
#include "myWorld.h"

myVector myPointLight::getDirection(myShadeRec & sr)
{
	return normalize(location - myVector(sr.hitPoint.x, sr.hitPoint.y, sr.hitPoint.z));
}

myRGBColor myPointLight::L(myShadeRec & sr)
{
	return ls * color;
}

bool myPointLight::inShadow(const myRay & shadowRay, const myShadeRec & sr) const
{
	double t;
	double dis = distance(shadowRay.o, myPoint(location));

	for (auto iter = sr.w.objects.cbegin(); iter != sr.w.objects.cend(); ++iter)
	{
		if ((*iter) != nullptr)
		{
			(*iter)->shadowHit(shadowRay, t);
			//if (t == dis)
			//{
			//	std::cout << "23333" << std::endl;
			//}
			if ((*iter)->shadowHit(shadowRay, t) && t < dis)
			{
				//std::cout << "inshadow\n";
				return true;
			}
			
		}
	}

	return false;
}
