#include "myShadeRec.h"

myShadeRec & myShadeRec::operator=(const myShadeRec & rhs)
{
	// TODO: �ڴ˴����� return ���
	if (this != &rhs)
	{
		hitAnObject = rhs.hitAnObject;
		materialPtr = rhs.materialPtr;
		hitPoint = rhs.hitPoint;
		localHitPoint = rhs.localHitPoint;
		normal = rhs.normal;
		ray = rhs.ray;
		t = rhs.t;
		dir = rhs.dir;
		depth = rhs.depth;
	}
	return *this;

}
