#pragma once
#include "myAmbient.h"
#include "myRGBColor.h"
#include "myGeometricObject.h"
#include "myViewPlane.h"
//#include "mySphere.h"
#include "myTracer.h"
#include "myCamera.h"


#include <vector>

class myWorld
{
public:

	myWorld() : cameraPtr(nullptr),
	backGroundColor(0, 0, 0), tracerPtr(nullptr),
	ambientPtr(new myAmbient) {}

	myWorld& operator=(const myWorld& rhs) {
		vp = rhs.vp;
		backGroundColor = rhs.backGroundColor;
		//sphere = rhs.sphere;
		colors = rhs.colors;
	}
	
	~myWorld() {
		if (colors != nullptr)
		{
			delete[] colors;
		}

		if (tracerPtr != nullptr)
		{
			delete tracerPtr;
		}

		if (ambientPtr != nullptr)
		{
			delete ambientPtr;
		}

		if (cameraPtr != nullptr)
		{
			delete cameraPtr;
		}

		for (auto iter = objects.begin(); iter != objects.end(); ++iter)
		{
			if ((*iter) != nullptr)
				delete (*iter);
		}

		for (auto iter = lights.begin(); iter != lights.end(); ++iter)
		{
			if ((*iter) != nullptr)
				delete (*iter);
		}
	}

	void build();
	void renderScene() const;
	void renderPerspective() const;
	void setPixel(const myRGBColor& pixelColor, int &index) const;
	void addObject(myGeometricObject* objectPtr) {
		objects.push_back(objectPtr);
	}
	void addLight(myLight* lightPtr) {
		lights.push_back(lightPtr);
	};
	myShadeRec hitBareBonesObjects(const myRay& ray);
	myShadeRec hitObjects(const myRay& ray);

	myRGBColor maxToOne(const myRGBColor& pixelColor) const;

	myViewPlane vp;
	myRGBColor backGroundColor;

	std::vector<myGeometricObject*> objects; // for mult objects
	std::vector<myLight*> lights;

	//mySphere sphere;   //for single object

	myCamera* cameraPtr;
	myLight* ambientPtr;
	myTracer *tracerPtr;
	int* colors;

};