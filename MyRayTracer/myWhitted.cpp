#include "myWhitted.h"
#include "myWorld.h"

myRGBColor myWhitted::traceRay(const myRay ray, const int depth) const
{
	if (depth > worldPtr->vp.maxDepth)
		return myRGBColor(0, 0, 0);
	else
	{
		myShadeRec sr(worldPtr->hitObjects(ray));
		if (sr.hitAnObject)
		{
			//std::cout << "hitted" << std::endl;
			sr.depth = depth;
			sr.ray = ray;
			return sr.materialPtr->shade(sr);
		}
		else
		{
			return worldPtr->backGroundColor;
		}
	}

}
