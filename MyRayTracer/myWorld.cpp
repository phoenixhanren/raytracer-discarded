#include "myWorld.h"
#include "myJittered.h"
#include "myRayCast.h"
#include "myPinhole.h"
#include "myPointLight.h"
#include "myMatte.h"
#include "mySphere.h"
#include "myPhong.h"
#include "myPlane.h"
#include "myReflective.h"
#include "myWhitted.h"
#include "myTriangle.h"
#include "myDirectional.h"
#include "myBoundMeshTriangle.h"
#include "myBVH.h"
#include "myTransparent.h"
#include "myRectangle.h"



void myWorld::build()
{
	vp.hres = 300;
	vp.vres = 300;
	vp.s = 0.5;
	vp.numSamples = 25;
	vp.maxDepth = 3;
	vp.sampler = new myJittered(vp.numSamples);

	backGroundColor = myRGBColor(0, 0, 0);
	tracerPtr = new myWhitted(this);

	myAmbient* ambientPtr = new myAmbient;
	ambientPtr->scaleRadiance(1.0);
	this->ambientPtr = ambientPtr;
	
	myPoint eye(0, 300, 500);
	myPoint lookAt(0, 100, 0);
	myVector up(0, 1, 0);
	myPinhole* pinholePtr = new myPinhole(eye, lookAt, up, 400, 1.0);
	pinholePtr->computeUVW();
	this->cameraPtr = pinholePtr;

	myPointLight* lightPtr = new myPointLight(6.0, myRGBColor(1, 1, 1), myVector(300, 300, 300));
	this->addLight(lightPtr);
	//myDirectional* dirPtr = new myDirectional(3.0, myRGBColor(1.0, 1.0, 1.0),
	//	myVector(300, 300, 300));
	//this->addLight(dirPtr);

	//20160606

	myLambertian* ambient = new myLambertian(0.23125, myRGBColor(1, 1, 1));
	myLambertian* diffuse = new myLambertian(0.2775, myRGBColor(1, 1, 1));
	myGlossySpecular* glossySpecular = new myGlossySpecular(2000, 0.5);
		//new myGlossySpecular(89.6, 0.773911);
	myPhong* phongPtr1 = new myPhong(ambient, diffuse, glossySpecular);

	myLambertian* ambient2 = new myLambertian(0, myRGBColor(1, 1, 1));
	myLambertian* diffuse2 = new myLambertian(0, myRGBColor(1, 1, 1));
	myGlossySpecular* glossySpecular2 = new myGlossySpecular(76.8, 0);

	myLambertian* ambient3 = new myLambertian(0.25, myRGBColor(1, 1, 1));
	myLambertian* diffuse3 = new myLambertian(0.5, myRGBColor(1, 1, 1));
	myGlossySpecular* glossySpecular3 = new myGlossySpecular(0.15, 100);
	myPhong* phongPtr2 = new myPhong(ambient2, diffuse2, glossySpecular2);
	myPerfectSpecular* perfectSpecular2 = new myPerfectSpecular();
	perfectSpecular2->setKr(0.1);
	perfectSpecular2->setCr(1);
	myPerfectTransmitter* trans = new myPerfectTransmitter(1.5, 0.9);
	myTransparent* ts = new myTransparent(phongPtr1, perfectSpecular2, trans);
	myTransparent* ts2 = new myTransparent(phongPtr2, perfectSpecular2, trans);
	myReflective* reflective3 = new myReflective(ambient3, diffuse3, glossySpecular3, perfectSpecular2);
	myReflective* reflective2 = new myReflective(ambient2, diffuse2, glossySpecular2, perfectSpecular2);
	myReflective* reflective1 = new myReflective(ambient, diffuse, glossySpecular, perfectSpecular2);

	////20160606
	float ka = 0.25;
	float kd = 0.75;
	myMesh* mesh = new myMesh;
	myMesh* mesh1 = new myMesh;
	std::vector<myMeshTriangle*> triangles;
	std::vector<myMeshTriangle*> triangles1;
	//char *fileName = "D:\\cg\\sphere.ply";
	//char *fileName = "D:\\cg\\chopper.ply";
	char *fileName = "D:\\cg\\raytracefromgroundup\\dragon_recon\\dragon_recon\\dragon_vrip.ply";
	char *fileName1 = "D:\\cg\\bunny\\bunny\\reconstruction\\bun_zipper.ply";
	char *fileName2 = "D:\\cg\\raytracefromgroundup\\PLYFiles\\PLYFiles";
	//char *fileName = "D:\\cg\\happy_recon\\happy_recon\\happy_vrip.ply";

	myPoint p0(-1000, 50, -200);
	myRectangle *r = new myRectangle(p0, myVector(0, 0, 5000), myVector(5000, 0, 0));

	r->setMaterial(reflective1);

	mySphere* sphere = new mySphere(myPoint(-10, 70, 170), 20);
	sphere->setMaterial(ts2);

	mySphere* sphere2 = new mySphere(myPoint(40, 70, 150), 20);
	sphere2->setMaterial(reflective1);

	mySphere* sphere3 = new mySphere(myPoint(-40, 70, 100), 20);
	sphere3->setMaterial(phongPtr1);

	myMatrix scale(1000, 1000, 1000, 's');
	myMatrix move(100, 0, 100, 't');
	myMatrix move1(-100, 0, -100, 't');
	myMatrix move2(0, 0, 0, 't');
	//readPly(fileName, mesh, triangles, scale, move1);
	//
	//computeMeshNormal(mesh, triangles);

	readPly(fileName1, mesh1, triangles1, scale, move2);
	computeMeshNormal(mesh1, triangles1);

	std::vector<myGeometricObject*> t;
	addObject(r);
	addObject(sphere);
	addObject(sphere2);
	addObject(sphere3);
	//for (auto iter = triangles.begin(); iter != triangles.end(); ++iter)
	//{
	//	(*iter)->setMaterial(phongPtr1);
	//	t.push_back(*iter);

	//}

	//myBVH* b = new myBVH(t, 0);
	//addObject(b);
	//b->setMaterial(phongPtr1);
	//std::cout << "finished constructed BVH" << std::endl;
	std::vector<myGeometricObject*> t1;
	for (auto iter = triangles1.begin(); iter != triangles1.end(); ++iter)
	{
		(*iter)->setMaterial(ts2);
		t1.push_back(*iter);

	}
	myBVH* b1 = new myBVH(t1, 0);

	std::cout << "finished constructed BVH" << std::endl;

	b1->setMaterial(ts2);

	addObject(b1);



	

	//mySphere* sphere_ptr1 = new mySphere(myPoint(180, 80, 60), 120);
	//myTriangle* trianglePtr = new myTriangle(myPoint(100, -80, 100), myPoint(0, -80, -100), myPoint(-100, -80, 100));
	//trianglePtr->setMaterial(reflective2);
	//addObject(trianglePtr);
	//sphere_ptr1->setMaterial(reflective2);	   							
	//addObject(sphere_ptr1);

	//mySphere* sphere_ptr2 = new mySphere(myPoint(-0.06, 0.12, -0.06), 0.02);
	//sphere_ptr2->setMaterial(reflective3);
	//addObject(sphere_ptr2);

	//mySphere* sphere_ptr3 = new mySphere(myPoint(-0.06, 0.08, -0.03), 0.02);
	//sphere_ptr3->setMaterial(reflective3);
	//addObject(sphere_ptr3);

	//mySphere* sphere_ptr4 = new mySphere(myPoint(0.0, 0.08, -0.06), 0.02);
	//sphere_ptr4->setMaterial(reflective3);
	//addObject(sphere_ptr4);

	////myPlane* plane_ptr1 = new myPlane(myPoint(-10, -10, -10), myNormal(0, 1, 0), myRGBColor());
	////plane_ptr1->setMaterial(phongPtr1);
	////addObject(plane_ptr1);




	//20160606

	//mySphere* spherePtr5 = new mySphere(myPoint(0, 0, 100), 10, myRGBColor(1, 0, 1));
	//spherePtr5->setMaterial(reflective);
	//this->addObject(spherePtr5);

	//mySphere* spherePtr6 = new mySphere(myPoint(0, 100, 0), 27, myRGBColor(1, 0, 1));
	//spherePtr6->setMaterial(reflective);
	//this->addObject(spherePtr6);

	//mySphere* spherePtr4 = new mySphere(myPoint(-29, 100, 0), 15, myRGBColor(0.5, 0.5, 0.5));
	//spherePtr4->setMaterial(reflective);
	//this->addObject(spherePtr4);

	//mySphere* spherePtr5 = new mySphere(myPoint(-29, 60, 0), 5, myRGBColor(0.75, 0.75, 0.75));
	//spherePtr5->setMaterial(reflective);
	//this->addObject(spherePtr5);

	//myVector temp = myVector(100, -150, 150) - myVector(-29, 60, 0);
	//myPlane* planePtr = new myPlane(myPoint(-29, 60, -10), myNormal(temp), myRGBColor(1, 1, 1));
	//planePtr->setMaterial(matterPtr);
	//this->addObject(planePtr);

	//mySphere* spherePtr6 = new mySphere(myPoint(0, -100, 0), 100, myRGBColor(0.25, 0.25, 0.25));
	//spherePtr6->setMaterial(reflective);
	//this->addObject(spherePtr6);

	//myPlane* planePtr = new myPlane(myPoint(0, 150, -150), myNormal(0, -150, 150), myRGBColor(1, 1, 1));
	//planePtr->setMaterial(phongPtr1);
	//this->addObject(planePtr);
	//myPlane* planePtr = new myPlane(myPoint(0, 0, 0), myNormal(1.0, 1.0, 1.0), myRGBColor(0.5, 0.5, 0.5));
	//std::cout << planePtr->getColor() << std::endl;
	////myPlane* planePtr1 = new myPlane(myPoint(0, -80, 0), myNormal(0, 0, 1.0), myRGBColor(0.3, 0.3, 0.3));


	//this->addObject(planePtr);
	//this->addObject(planePtr1);

	//myPoint eye(0, 0, 500);
	//myPoint lookAt(0, 0, -1);
	//myVector up(0, 1, 0);
	//myPinhole* pinholePtr = new myPinhole(eye, lookAt, up, 250, 1.0);
	//pinholePtr->computeUVW();
	//this->cameraPtr = pinholePtr;

	//myPointLight* lightPtr = new myPointLight(100.0, myRGBColor(1, 1, 1), myVector(0, -300, 00));
	//this->addLight(lightPtr);

	//myMatte* matterPtr = new myMatte(new myLambertian(), new myLambertian());
	//matterPtr->setKA(0.25);
	//matterPtr->setKD(0.65);
	//matterPtr->setCD(myRGBColor(1, 0, 0));

	//mySphere* spherePtr = new mySphere(myPoint(10, -5, 0), 27, myRGBColor(1, 0, 0));
	//spherePtr->setMaterial(matterPtr);
	////spherePtr->getMaterial()->shade(myShadeRec(*this));
	//this->addObject(spherePtr);

	//myMatte* matterPtr1 = new myMatte(new myLambertian(), new myLambertian());
	//matterPtr1->setKA(0.25);
	//matterPtr1->setKD(0.65);
	//matterPtr1->setCD(myRGBColor(1, 1, 0));

	//mySphere* spherePtr1 = new mySphere(myPoint(-50, -5, 0), 27, myRGBColor(1, 1, 0));
	//spherePtr1->setMaterial(matterPtr1);
	//this->addObject(spherePtr1);
	////std::cout << "123" << std::endl;


	//myLambertian* ambient = new myLambertian(0.25, myRGBColor(1, 1, 0));
	//myLambertian* diffuse = new myLambertian(0.6, myRGBColor(1, 1, 0));
	//myGlossySpecular* glossySpecular = new myGlossySpecular(5, 0.2);	
	//myPhong* phongPtr1 = new myPhong(ambient, diffuse, glossySpecular);
	////mySphere* spherePtr2 = new mySphere(myPoint(50, -50, 0), 27, myRGBColor(1, 0, 0));
	////spherePtr2->setMaterial(phongPtr1);
	////this->addObject(spherePtr2);

	//myLambertian* ambient1 = new myLambertian(0.25, myRGBColor(1, 0, 0));
	//myLambertian* diffuse1 = new myLambertian(0.5, myRGBColor(1, 0, 0));
	//myGlossySpecular* glossySpecular1 = new myGlossySpecular(100, 0.15);
	//myPerfectSpecular* perfectSpecular1 = new myPerfectSpecular();
	//perfectSpecular1->setKr(0.75);
	//perfectSpecular1->setCr(1);
	//myReflective* reflective = new myReflective(ambient1, diffuse1, glossySpecular1, perfectSpecular1);
	//mySphere* spherePtr3 = new mySphere(myPoint(0, -100, -500), 100, myRGBColor(1, 0, 1));
	//spherePtr3->setMaterial(phongPtr1);
	//this->addObject(spherePtr3);

	//mySphere* spherePtr4 = new mySphere(myPoint(0, 70, 0), 27, myRGBColor(1, 0, 1));
	//spherePtr4->setMaterial(phongPtr1);
	//this->addObject(spherePtr4);

	//mySphere* spherePtr5 = new mySphere(myPoint(0, 50, -20), 10, myRGBColor(1, 0, 1));
	//spherePtr5->setMaterial(phongPtr1);
	//this->addObject(spherePtr5);

	//myPoint tempPoint = myPoint(0, -1000, -1000);
	//
	//myNormal temp = myNormal(myPoint(0, -300, 00) - tempPoint);
	//myPlane* planePtr = new myPlane(tempPoint, temp, myRGBColor(1, 1, 1));
	//planePtr->setMaterial(phongPtr1);
	//this->addObject(planePtr);

	//mySphere* spherePtr4 = new mySphere(myPoint(40, 0, 70), 27, myRGBColor(1, 0, 1));
	//spherePtr4->setMaterial(phongPtr1);
	//this->addObject(spherePtr4);

	//mySphere* spherePtr6 = new mySphere(myPoint(10, 0, 70), 10, myRGBColor(1, 0, 1));
	//spherePtr6->setMaterial(phongPtr1);
	//this->addObject(spherePtr6);

	//mySphere* spherePtr5 = new mySphere(myPoint(40, 0, 70), 20, myRGBColor(1, 0, 1));
	//spherePtr5->setMaterial(phongPtr1);
	//this->addObject(spherePtr5);

	//myLambertian* ambient2 = new myLambertian(0.25, myRGBColor(0, 1, 0));
	//myLambertian* diffuse2 = new myLambertian(0.5, myRGBColor(0, 1, 0));
	//myReflective* reflective2 = new myReflective(ambient2, diffuse2, glossySpecular1, perfectSpecular1);
	//mySphere* spherePtr4 = new mySphere(myPoint(50, 70, 30), 27, myRGBColor(1, 0, 1));
	//spherePtr4->setMaterial(reflective2);
	//this->addObject(spherePtr4);

	//mySphere* spherePtr4 = new mySphere(myPoint(-29, 100, 0), 15, myRGBColor(0.5, 0.5, 0.5));
	//spherePtr4->setMaterial(reflective);
	//this->addObject(spherePtr4);

	//mySphere* spherePtr5 = new mySphere(myPoint(-29, 60, 0), 5, myRGBColor(0.75, 0.75, 0.75));
	//spherePtr5->setMaterial(reflective);
	//this->addObject(spherePtr5);

 	//myVector temp = myVector(100, -150, 150) - myVector(-29, 60, 0);
	//myPlane* planePtr = new myPlane(myPoint(-29, 60, -10), myNormal(temp), myRGBColor(1, 1, 1));
	//planePtr->setMaterial(matterPtr);
	//this->addObject(planePtr);

	//mySphere* spherePtr6 = new mySphere(myPoint(0, -100, 0), 100, myRGBColor(0.25, 0.25, 0.25));
	//spherePtr6->setMaterial(reflective);
	//this->addObject(spherePtr6);

	//myPlane* planePtr = new myPlane(myPoint(0, -50, -27), myNormal(0, 0, 1), myRGBColor(1, 1, 1));
	//planePtr->setMaterial(phongPtr1);
	//this->addObject(planePtr);
	//myPlane* planePtr = new myPlane(myPoint(0, 0, 0), myNormal(1.0, 1.0, 1.0), myRGBColor(0.5, 0.5, 0.5));
	//std::cout << planePtr->getColor() << std::endl;
	////myPlane* planePtr1 = new myPlane(myPoint(0, -80, 0), myNormal(0, 0, 1.0), myRGBColor(0.3, 0.3, 0.3));


	//this->addObject(planePtr);
	//this->addObject(planePtr1);
	
	// colors
//myMatte* matte_ptr1 = new myMatte;
//matte_ptr1->setKA(ka);
//matte_ptr1->setKD(kd);
//matte_ptr1->setCD(myRGBColor(1, 1, 0));
//mySphere*	sphere_ptr1 = new mySphere(myPoint(5, 30, 0), 10);
//sphere_ptr1->setMaterial(matte_ptr1);	   							// yellow
//addObject(sphere_ptr1);
/*
myRGBColor yellow(1, 1, 0);										// yellow
myRGBColor brown(0.71, 0.40, 0.16);								// brown
myRGBColor darkGreen(0.0, 0.41, 0.41);							// darkGreen
myRGBColor orange(1, 0.75, 0);									// orange
myRGBColor green(0, 0.6, 0.3);									// green
myRGBColor lightGreen(0.65, 1, 0.30);								// light green
myRGBColor darkYellow(0.61, 0.61, 0);								// dark yellow
myRGBColor lightPurple(0.65, 0.3, 1);								// light purple
myRGBColor darkPurple(0.5, 0, 1);									// dark purple
myRGBColor grey(0.25);											// grey


																// Matte material reflection coefficients - common to all materials

//float ka = 0.25;
//float kd = 0.75;


// spheres

myMatte* matte_ptr1 = new myMatte;
matte_ptr1->setKA(ka);
matte_ptr1->setKD(kd);
matte_ptr1->setCD(yellow);
mySphere*	sphere_ptr1 = new mySphere(myPoint(5, 3, 0), 30, myRGBColor(yellow));
sphere_ptr1->setMaterial(matte_ptr1);	   							// yellow
addObject(sphere_ptr1);

myMatte* matte_ptr2 = new myMatte;
matte_ptr2->setKA(ka);
matte_ptr2->setKD(kd);
matte_ptr2->setCD(brown);
mySphere*	sphere_ptr2 = new mySphere(myPoint(45, -7, -60), 20, brown);
sphere_ptr2->setMaterial(matte_ptr2);								// brown
addObject(sphere_ptr2);


myMatte* matte_ptr3 = new myMatte;
matte_ptr3->setKA(ka);
matte_ptr3->setKD(kd);
matte_ptr3->setCD(darkGreen);
mySphere*	sphere_ptr3 = new mySphere(myPoint(40, 43, -100), 17, darkGreen);
sphere_ptr3->setMaterial(matte_ptr3);								// dark green
addObject(sphere_ptr3);

myMatte* matte_ptr4 = new myMatte;
matte_ptr4->setKA(ka);
matte_ptr4->setKD(kd);
matte_ptr4->setCD(orange);
mySphere*	sphere_ptr4 = new mySphere(myPoint(-20, 28, -15), 20, orange);
sphere_ptr4->setMaterial(matte_ptr4);								// orange
addObject(sphere_ptr4);

myMatte* matte_ptr5 = new myMatte;
matte_ptr5->setKA(ka);
matte_ptr5->setKD(kd);
matte_ptr5->setCD(green);
mySphere*	sphere_ptr5 = new mySphere(myPoint(-25, -7, -35), 27, green);
sphere_ptr5->setMaterial(matte_ptr5);								// green
addObject(sphere_ptr5);

myMatte* matte_ptr6 = new myMatte;
matte_ptr6->setKA(ka);
matte_ptr6->setKD(kd);
matte_ptr6->setCD(lightGreen);
mySphere*	sphere_ptr6 = new mySphere(myPoint(20, -27, -35), 25, lightGreen);
sphere_ptr6->setMaterial(matte_ptr6);								// light green
addObject(sphere_ptr6);

myMatte* matte_ptr7 = new myMatte;
matte_ptr7->setKA(ka);
matte_ptr7->setKD(kd);
matte_ptr7->setCD(green);
mySphere*	sphere_ptr7 = new mySphere(myPoint(35, 18, -35), 22, green);
sphere_ptr7->setMaterial(matte_ptr7);   							// green
addObject(sphere_ptr7);

myMatte* matte_ptr8 = new myMatte;
matte_ptr8->setKA(ka);
matte_ptr8->setKD(kd);
matte_ptr8->setCD(brown);
mySphere*	sphere_ptr8 = new mySphere(myPoint(-57, -17, -50), 15, brown);
sphere_ptr8->setMaterial(matte_ptr8);								// brown
addObject(sphere_ptr8);

myMatte* matte_ptr9 = new myMatte;
matte_ptr9->setKA(ka);
matte_ptr9->setKD(kd);
matte_ptr9->setCD(lightGreen);
mySphere*	sphere_ptr9 = new mySphere(myPoint(-47, 16, -80), 23);
sphere_ptr9->setMaterial(matte_ptr9);								// light green
addObject(sphere_ptr9);

myMatte* matte_ptr10 = new myMatte;
matte_ptr10->setKA(ka);
matte_ptr10->setKD(kd);
matte_ptr10->setCD(darkGreen);
mySphere*	sphere_ptr10 = new mySphere(myPoint(-15, -32, -60), 22);
sphere_ptr10->setMaterial(matte_ptr10);     						// dark green
addObject(sphere_ptr10);

myMatte* matte_ptr11 = new myMatte;
matte_ptr11->setKA(ka);
matte_ptr11->setKD(kd);
matte_ptr11->setCD(darkYellow);
mySphere*	sphere_ptr11 = new mySphere(myPoint(-35, -37, -80), 22);
sphere_ptr11->setMaterial(matte_ptr11);							// dark yellow
addObject(sphere_ptr11);

myMatte* matte_ptr12 = new myMatte;
matte_ptr12->setKA(ka);
matte_ptr12->setKD(kd);
matte_ptr12->setCD(darkYellow);
mySphere*	sphere_ptr12 = new mySphere(myPoint(10, 43, -80), 22);
sphere_ptr12->setMaterial(matte_ptr12);							// dark yellow
addObject(sphere_ptr12);

myMatte* matte_ptr13 = new myMatte;
matte_ptr13->setKA(ka);
matte_ptr13->setKD(kd);
matte_ptr13->setCD(darkYellow);
mySphere*	sphere_ptr13 = new mySphere(myPoint(30, -7, -80), 10);
sphere_ptr13->setMaterial(matte_ptr13);
addObject(sphere_ptr13);											// dark yellow (hidden)

myMatte* matte_ptr14 = new myMatte;
matte_ptr14->setKA(ka);
matte_ptr14->setKD(kd);
matte_ptr14->setCD(darkGreen);
mySphere*	sphere_ptr14 = new mySphere(myPoint(-40, 48, -110), 18);
sphere_ptr14->setMaterial(matte_ptr14); 							// dark green
addObject(sphere_ptr14);

myMatte* matte_ptr15 = new myMatte;
matte_ptr15->setKA(ka);
matte_ptr15->setKD(kd);
matte_ptr15->setCD(brown);
mySphere*	sphere_ptr15 = new mySphere(myPoint(-10, 53, -120), 18);
sphere_ptr15->setMaterial(matte_ptr15); 							// brown
addObject(sphere_ptr15);

myMatte* matte_ptr16 = new myMatte;
matte_ptr16->setKA(ka);
matte_ptr16->setKD(kd);
matte_ptr16->setCD(lightPurple);
mySphere*	sphere_ptr16 = new mySphere(myPoint(-55, -52, -100), 10);
sphere_ptr16->setMaterial(matte_ptr16);							// light purple
addObject(sphere_ptr16);

myMatte* matte_ptr17 = new myMatte;
matte_ptr17->setKA(ka);
matte_ptr17->setKD(kd);
matte_ptr17->setCD(brown);
mySphere*	sphere_ptr17 = new mySphere(myPoint(5, -52, -100), 15);
sphere_ptr17->setMaterial(matte_ptr17);							// browm
addObject(sphere_ptr17);

myMatte* matte_ptr18 = new myMatte;
matte_ptr18->setKA(ka);
matte_ptr18->setKD(kd);
matte_ptr18->setCD(darkPurple);
mySphere*	sphere_ptr18 = new mySphere(myPoint(-20, -57, -120), 15);
sphere_ptr18->setMaterial(matte_ptr18);							// dark purple
addObject(sphere_ptr18);

myMatte* matte_ptr19 = new myMatte;
matte_ptr19->setKA(ka);
matte_ptr19->setKD(kd);
matte_ptr19->setCD(darkGreen);
mySphere*	sphere_ptr19 = new mySphere(myPoint(55, -27, -100), 17);
sphere_ptr19->setMaterial(matte_ptr19);							// dark green
addObject(sphere_ptr19);

myMatte* matte_ptr20 = new myMatte;
matte_ptr20->setKA(ka);
matte_ptr20->setKD(kd);
matte_ptr20->setCD(brown);
mySphere*	sphere_ptr20 = new mySphere(myPoint(50, -47, -120), 15);
sphere_ptr20->setMaterial(matte_ptr20);							// browm
addObject(sphere_ptr20);

myMatte* matte_ptr21 = new myMatte;
matte_ptr21->setKA(ka);
matte_ptr21->setKD(kd);
matte_ptr21->setCD(lightPurple);
mySphere*	sphere_ptr21 = new mySphere(myPoint(70, -42, -150), 10);
sphere_ptr21->setMaterial(matte_ptr21);							// light purple
addObject(sphere_ptr21);

myMatte* matte_ptr22 = new myMatte;
matte_ptr22->setKA(ka);
matte_ptr22->setKD(kd);
matte_ptr22->setCD(lightPurple);
mySphere*	sphere_ptr22 = new mySphere(myPoint(5, 73, -130), 12);
sphere_ptr22->setMaterial(matte_ptr22);							// light purple
addObject(sphere_ptr22);

myMatte* matte_ptr23 = new myMatte;
matte_ptr23->setKA(ka);
matte_ptr23->setKD(kd);
matte_ptr23->setCD(darkPurple);
mySphere*	sphere_ptr23 = new mySphere(myPoint(66, 21, -130), 13);
sphere_ptr23->setMaterial(matte_ptr23);							// dark purple
addObject(sphere_ptr23);

myMatte* matte_ptr24 = new myMatte;
matte_ptr24->setKA(ka);
matte_ptr24->setKD(kd);
matte_ptr24->setCD(lightPurple);
mySphere*	sphere_ptr24 = new mySphere(myPoint(72, -12, -140), 12);
sphere_ptr24->setMaterial(matte_ptr24);							// light purple
addObject(sphere_ptr24);

myMatte* matte_ptr25 = new myMatte;
matte_ptr25->setKA(ka);
matte_ptr25->setKD(kd);
matte_ptr25->setCD(green);
mySphere*	sphere_ptr25 = new mySphere(myPoint(64, 5, -160), 11);
sphere_ptr25->setMaterial(matte_ptr25);					 		// green
addObject(sphere_ptr25);

myMatte* matte_ptr26 = new myMatte;
matte_ptr26->setKA(ka);
matte_ptr26->setKD(kd);
matte_ptr26->setCD(lightPurple);
mySphere*	sphere_ptr26 = new mySphere(myPoint(55, 38, -160), 12);
sphere_ptr26->setMaterial(matte_ptr26);							// light purple
addObject(sphere_ptr26);

myMatte* matte_ptr27 = new myMatte;
matte_ptr27->setKA(ka);
matte_ptr27->setKD(kd);
matte_ptr27->setCD(lightPurple);
mySphere*	sphere_ptr27 = new mySphere(myPoint(-73, -2, -160), 12);
sphere_ptr27->setMaterial(matte_ptr27);							// light purple
addObject(sphere_ptr27);

myMatte* matte_ptr28 = new myMatte;
matte_ptr28->setKA(ka);
matte_ptr28->setKD(kd);
matte_ptr28->setCD(darkPurple);
mySphere*	sphere_ptr28 = new mySphere(myPoint(30, -62, -140), 15);
sphere_ptr28->setMaterial(matte_ptr28); 							// dark purple
addObject(sphere_ptr28);

myMatte* matte_ptr29 = new myMatte;
matte_ptr29->setKA(ka);
matte_ptr29->setKD(kd);
matte_ptr29->setCD(darkPurple);
mySphere*	sphere_ptr29 = new mySphere(myPoint(25, 63, -140), 15);
sphere_ptr29->setMaterial(matte_ptr29);							// dark purple
addObject(sphere_ptr29);

myMatte* matte_ptr30 = new myMatte;
matte_ptr30->setKA(ka);
matte_ptr30->setKD(kd);
matte_ptr30->setCD(darkPurple);
mySphere*	sphere_ptr30 = new mySphere(myPoint(-60, 46, -140), 15);
sphere_ptr30->setMaterial(matte_ptr30); 							// dark purple
addObject(sphere_ptr30);

myMatte* matte_ptr31 = new myMatte;
matte_ptr31->setKA(ka);
matte_ptr31->setKD(kd);
matte_ptr31->setCD(lightPurple);
mySphere*	sphere_ptr31 = new mySphere(myPoint(-30, 68, -130), 12);
sphere_ptr31->setMaterial(matte_ptr31); 							// light purple
addObject(sphere_ptr31);

myMatte* matte_ptr32 = new myMatte;
matte_ptr32->setKA(ka);
matte_ptr32->setKD(kd);
matte_ptr32->setCD(green);
mySphere*	sphere_ptr32 = new mySphere(myPoint(58, 56, -180), 11);
sphere_ptr32->setMaterial(matte_ptr32);							//  green
addObject(sphere_ptr32);

myMatte* matte_ptr33 = new myMatte;
matte_ptr33->setKA(ka);
matte_ptr33->setKD(kd);
matte_ptr33->setCD(green);
mySphere*	sphere_ptr33 = new mySphere(myPoint(-63, -39, -180), 11);
sphere_ptr33->setMaterial(matte_ptr33);							// green 
addObject(sphere_ptr33);

myMatte* matte_ptr34 = new myMatte;
matte_ptr34->setKA(ka);
matte_ptr34->setKD(kd);
matte_ptr34->setCD(lightPurple);
mySphere*	sphere_ptr34 = new mySphere(myPoint(46, 68, -200), 10);
sphere_ptr34->setMaterial(matte_ptr34);							// light purple
addObject(sphere_ptr34);

myMatte* matte_ptr35 = new myMatte;
matte_ptr35->setKA(ka);
matte_ptr35->setKD(kd);
matte_ptr35->setCD(lightPurple);
mySphere*	sphere_ptr35 = new mySphere(myPoint(-3, -72, -130), 12);
sphere_ptr35->setMaterial(matte_ptr35);							// light purple
addObject(sphere_ptr35);


// vertical plane

myMatte* matte_ptr36 = new myMatte;
matte_ptr36->setKA(ka);
matte_ptr36->setKD(kd);
matte_ptr36->setCD(grey);
myPlane* plane_ptr = new myPlane(myPoint(0, 0, -150), myNormal(0, 0, 1), grey);
plane_ptr->setMaterial(matte_ptr36);
addObject(plane_ptr);
*/
}

void myWorld::renderScene() const
{
////	charpter 3
//	myRGBColor pixelColor;
//	myRay ray;
//	double zw = 100.0;
//	double x, y;
//	ray.dir = myVector(0, 0, -1);
//	int index = 0;
//	for (int r = 0; r < vp.vres; r++)
//		for (int c = 0; c < vp.hres; c++)
//		{
//			x = vp.s * (c - 0.5 * (vp.hres - 1.0));
//			y = vp.s * (r - 0.5 * (vp.vres - 1.0));
//			ray.o = myPoint(x, y, zw);
//			pixelColor = tracerPtr->traceRay(ray);
//			//std::cout << index << std::endl;
//			setPixel(pixelColor, index);
//		}
//
	////charpter 4
	//myRGBColor pixelColor;
	//myRay ray;
	//double zw = 100.0;
	//int n = static_cast<int>(
	//	sqrt(static_cast<double>(vp.numSamples)));
	//myPoint pp; // sample point on a pixel
	//int index = 0;
	//ray.dir = myVector(0, 0, -1);
	//for (int r = 0; r < vp.vres; ++r)
	//{
	//	for (int c = 0; c < vp.hres; ++c)
	//	{
	//		pixelColor = myRGBColor(0, 0, 0);
	//		////均匀采样
	//		//for (int p = 0; p < n; ++p)
	//		//{
	//		//	for (int q = 0; q < n; ++q)
	//		//	{
	//		//		pp.x = vp.s * (c - 0.5 * vp.hres +
	//		//			(q + 0.5) / n);
	//		//		pp.y = vp.s * (r - 0.5 * vp.vres +
	//		//			(p + 0.5) / n);
	//		//		ray.o = myPoint(pp.x, pp.y, zw);
	//		//		pixelColor += tracerPtr->traceRay(ray);
	//		//	}
	//		//}

	//		////随机采样
	//		//for (int p = 0; p < vp.numSamples; ++p)
	//		//{
	//		//	pp.x = vp.s * (c - 0.5 * vp.hres + rand() / double(RAND_MAX));
	//		//	pp.y = vp.s * (r - 0.5 * vp.vres + rand() / double(RAND_MAX));
	//		//	ray.o = myPoint(pp.x, pp.y, zw);
	//		//	pixelColor += tracerPtr->traceRay(ray);
	//		//}

	//		//抖动采样
	//		for (int p = 0; p < n; ++p)
	//		{
	//			for (int q = 0; q < n; ++q)
	//			{
	//				pp.x = vp.s * (c - 0.5 * vp.hres +
	//					(q + rand() / double(RAND_MAX)) / n);
	//				pp.y = vp.s * (r - 0.5 * vp.vres +
	//					(p + rand() / double(RAND_MAX)) / n);
	//				ray.o = myPoint(pp.x, pp.y, zw);
	//				pixelColor += tracerPtr->traceRay(ray);
	//			}
	//		}
	//		pixelColor /= vp.numSamples;
	//		setPixel(pixelColor, index);
	//	}
	//}

	//charpter 5-1
	myRGBColor pixelColor;
	myRay ray;
	double zw = 100.0;
	myPoint sp;
	myPoint pp;

	vp.sampler = new myJittered(25);
	vp.numSamples = 25;
	int index = 0;
	ray.dir = myVector(0, 0, -1);
	for (int r = 0; r < vp.vres; ++r)
	{
		for (int c = 0; c < vp.hres; ++c)
		{
			pixelColor = myRGBColor(0, 0, 0);

			for (int j = 0; j < vp.numSamples; ++j)
			{
				sp = vp.sampler->sampleUnitSquare();
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.o = myPoint(pp.x, pp.y, zw);
				pixelColor += tracerPtr->traceRay(ray);
			}
			pixelColor /= vp.numSamples;
			setPixel(pixelColor, index);
		}
	}
}

void myWorld::renderPerspective() const
{
	myRGBColor pixelColor;
	myRay ray;
	double eye = 500;
	double d = 200;
	int index = 0;
	ray.o = myPoint(0.0, 0.0, eye);

	for (int r = 0; r < vp.vres; ++r)
	{
		for (int c = 0; c < vp.hres; ++c)
		{
			ray.dir = normalize(myVector(vp.s * (c - 0.5 * (vp.hres - 1.0)),
				vp.s * (r - 0.5 * (vp.vres - 1.0)), -d));
			pixelColor = tracerPtr->traceRay(ray);
			setPixel(pixelColor, index);
		}
	}
}

void myWorld::setPixel(const myRGBColor & pixelColor, int &index) const
{
	myRGBColor temp = maxToOne(pixelColor);
	//if (temp.r != 0)
	//{
	//	std::cout << temp.r << temp.b << temp.g << std::endl;
	//}
		
	colors[index++] = static_cast<int>(temp.r * 255.0);
	colors[index++] = static_cast<int>(temp.g * 255.0);
	colors[index++] = static_cast<int>(temp.b * 255.0);
}

myShadeRec myWorld::hitBareBonesObjects(const myRay & ray)
{
	//myShadeRec sr(*this);
	myShadeRec sr(*this);
	double t;
	double tmin = INFINITY;

	for (auto iter = objects.cbegin(); iter != objects.cend(); ++iter)
	{
		if (*iter != nullptr)
		{
			//std::cout << (*iter)->getColor().r;
			if ((*iter)->hit(ray, t, sr) && (t < tmin))
			{
				sr.hitAnObject = true;
				tmin = t;
				sr.color = (*iter)->getColor();
				//std::cout << ray << std::endl;
			}
		}
	}
	return sr;	
}

myShadeRec myWorld::hitObjects(const myRay & ray) 
{
	myShadeRec sr(*this);
	double t;
	myNormal normal;
	myPoint localHitPoint;
	double tMin = INFINITY;
	
	for (auto iter = objects.cbegin(); iter != objects.cend(); ++iter)
	{
		if (*iter == nullptr)
			continue;
		if ((*iter)->hit(ray, t, sr) && (t < tMin))
		{
			//std::cout << (*iter)->getMaterial() << std::endl;
			sr.hitAnObject = true;
			tMin = t;
			sr.materialPtr = (*iter)->getMaterial();
			sr.hitPoint = ray.o + t * ray.dir;
			//if (sr.materialPtr == nullptr)
			//{
			//	sr.color = (*iter)->getColor();
			//	//std::cout << sr.hitPoint << std::endl;
			//	//std::cout << sr.color << std::endl;
			//	sr.color = myRGBColor(0.5, 0.5, 0.5);
			//}
			//
			normal = sr.normal;
			localHitPoint = sr.localHitPoint;
		}
	}

	if (sr.hitAnObject)
	{
		sr.t = tMin;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
	}


	return sr;
}

myRGBColor myWorld::maxToOne(const myRGBColor & pixelColor) const
{
	double maxValue = pixelColor.r;
	if (maxValue < pixelColor.g)
		maxValue = pixelColor.g;
	if (maxValue < pixelColor.b)
		maxValue = pixelColor.b;
	if (maxValue > 1.0)
		return myRGBColor(pixelColor.r / maxValue, pixelColor.g / maxValue,
			pixelColor.b / maxValue);
	else
		return pixelColor;
		
}
