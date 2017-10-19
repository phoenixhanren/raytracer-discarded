#pragma once
#include "mySampler.h"

class myViewPlane
{
public:
	int hres;   //horizontal image resolution
	int vres;   //vertical image resolution
	double s = 1.0;   //pixel size

	mutable int numSamples; //sampleNumber
	mutable mySampler* sampler;
	int maxDepth = 5;

};