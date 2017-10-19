#include "myBVH.h"
#include <algorithm>

int myBVH::count;

myBVH::myBVH(std::vector<myGeometricObject*> objects, int AXIS)
{
	create(objects, AXIS);

}

bool myBVH::hit(const myRay & ray, double & tMin, myShadeRec & sr) const
{
	if (bbox.hit(ray))
	{
		myShadeRec leftRec(sr), rightRec(sr);

		bool leftHit = false;
		bool rightHit = false;

		if ((left != nullptr) && (left->hit(ray, tMin, leftRec)))
		{
			leftHit = true;
		}

		if ((right != nullptr) && (right->hit(ray, tMin, rightRec)))
		{
			rightHit = true;
		}

		if (leftHit && rightHit)
		{
			if (leftRec.t < rightRec.t)
				sr = leftRec;
			else
				sr = rightRec;
			return true;
		}
		else if (leftHit)
		{
			sr = leftRec;
			return true;
		}
		else if (rightHit)
		{
			sr = rightRec;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

bool myBVH::shadowHit(const myRay & shadowRay, double & tMin) const
{
	if (bbox.hit(shadowRay))
	{


		bool leftHit = false;
		bool rightHit = false;

		if ((left != nullptr) && (left->shadowHit(shadowRay, tMin)))
		{
			leftHit = true;
		}

		if ((right != nullptr) && (right->shadowHit(shadowRay, tMin)))
		{
			rightHit = true;
		}

		if (leftHit && rightHit)
		{
			return true;
		}
		else if (leftHit)
		{
			return true;
		}
		else if (rightHit)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

myBBox myBVH::getBBox()
{
	return bbox;
}

void myBVH::create(std::vector<myGeometricObject*> objects, int AXIS)
{
	int n = objects.size();

	//if (n == 0)
	//{
	//	left = nullptr;
	//	right = nullptr;
	//	bbox = myBBox();
	//	return;
	//}
	if (n == 1)
	{
		left = objects[0];
		right = nullptr;
		bbox = left->getBBox();
	}

	else if (n == 2)
	{
		left = objects[0];
		right = objects[1];
		bbox = combine(left->getBBox(), right->getBBox());
	}
	else
	{

		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			//std::cout << (*iter)->getBBox().z0 << " " << (*iter)->getBBox().z1 << std::endl;
			bbox = combine(bbox, (*iter)->getBBox());
		}

		double midPoint;
		std::vector<myGeometricObject*>::iterator iter;

		if (AXIS == 0)
		{
			midPoint = (bbox.x0 + bbox.x1) / 2.0;
			iter = std::partition(objects.begin(), objects.end(), 
				[&midPoint](myGeometricObject* object)->bool {
				//std::cout << object->getBBox().x1 << std::endl;
				return object->getBBox().x1 < midPoint;
			});
		}
		else if (AXIS == 1)
		{
			midPoint = (bbox.y0 + bbox.y1) / 2.0;
			iter = std::partition(objects.begin(), objects.end(),
				[&midPoint](myGeometricObject* object)->bool {
				return object->getBBox().y1 < midPoint;
			});
		}
		else
		{
			midPoint = (bbox.z0 + bbox.z1) / 2.0;
			iter = std::partition(objects.begin(), objects.end(),
				[&midPoint](myGeometricObject* object)->bool {
				return object->getBBox().z1 < midPoint;
			});
		}
		//++count;
		//std::cout << count << std::endl;
		//if (count >= 702)
		//{
		//	std::cout << "lslsls" << std::endl;
		//}
		//std::cout << "lalala" << std::endl;

		if (iter == objects.begin())
		{
			left = objects[0];
			right = new myBVH(std::vector<myGeometricObject*>(iter + 1, objects.end()), (AXIS + 1) % 3);
			bbox = combine(left->getBBox(), right->getBBox());
		}
		else if (iter == objects.end())
		{
			right = objects[0];
			left = new myBVH(std::vector<myGeometricObject*>(objects.begin() + 1, iter), (AXIS + 1) % 3);
			bbox = combine(left->getBBox(), right->getBBox());
		}
		else
		{
			left = new myBVH(std::vector<myGeometricObject*>(objects.begin(), iter), (AXIS + 1) % 3);
			right = new myBVH(std::vector<myGeometricObject*>(iter, objects.end()), (AXIS + 1) % 3);
			bbox = combine(left->getBBox(), right->getBBox());
		}

	}
}
