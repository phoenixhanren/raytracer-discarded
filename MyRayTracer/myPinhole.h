#pragma once
#include "myCamera.h"
#include "myRGBColor.h"

class myPinhole : public myCamera
{
public:

	myPinhole() : myCamera(), d(1.0), zoom(1.0) {}

	myPinhole(myPoint& _eye, myPoint& _lookat, myVector& _up,
		double _d, double _zoom) :
		myCamera(_eye, _lookat, _up), d(_d), zoom(_zoom) {}

	virtual ~myPinhole() override {}

	myVector rayDirecton(const myPoint& p) const {
		myVector dir = p.x * u + p.y * v - d * w;
		return normalize(dir);
	}

	virtual int*** renderScene(myWorld &w) override;

private:
	
	void maxToOne1(myRGBColor &L);
	double d; //view-plane distance
	double zoom = 1.0; //zoom factor
};