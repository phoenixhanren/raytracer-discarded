#pragma once
class myWorld;
class myMaterial;

#include "myMath.h"
#include "myRGBColor.h"

class myShadeRec
{
public:


	myShadeRec(myWorld& wr) : hitAnObject(false),  localHitPoint(), 
		normal(), w(wr),  color(0, 0, 0), depth(0){}
	myShadeRec(const myShadeRec &sr) :
		hitAnObject(sr.hitAnObject), materialPtr(sr.materialPtr),
		hitPoint(sr.hitPoint), localHitPoint(sr.localHitPoint),
		normal(sr.normal), ray(sr.ray), t(sr.t),
		depth(sr.depth), w(sr.w), dir(sr.dir) {}

	myShadeRec &operator=(const myShadeRec& rhs);

	bool hitAnObject;  // did the ray hit an object;
	myMaterial* materialPtr; //nearest object's material
	myPoint hitPoint;  //world coordinates of hit point
	myPoint localHitPoint;  //for attaching textures to objects
	myNormal normal; ////normal at hit point

	myRay ray; 
	double t;
	int depth; //recursion depth
	myVector dir; //for area lights
	myRGBColor color;  //only use for charpter3

	myWorld &w;
};