#include "myShadeRec.h"

myShadeRec & myShadeRec::operator=(const myShadeRec & rhs)
{
	// TODO: 在此处插入 return 语句
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
