#pragma once
#include "myMath.h"
class myWorld;

class myCamera
{
public:
	myCamera() : eye(0, 0, 500), lookat(0, 0, 0),
	up(0, 1, 0), u(1, 0, 0), v(0, 1, 0), w(0, 0, 1) {}
	myCamera(myPoint& _eye, myPoint& _lookat, myVector& _up) : 
		eye(_eye), lookat(_lookat), up(_up) {
		computeUVW();
	}

	myCamera(myPoint& _eye, myPoint& _lookat, myVector& _up,
		myVector& _u, myVector& _v, myVector& _w) :
		eye(_eye), lookat(_lookat), up(_up), u(_u),
		v(_v), w(_w) {}

	virtual ~myCamera() {}

	void computeUVW();
	virtual int*** renderScene(myWorld& w) = 0;


protected:
	myPoint eye;
	myPoint lookat;
	myVector up;
	myVector u, v, w;
	int* colors = nullptr;
	
};