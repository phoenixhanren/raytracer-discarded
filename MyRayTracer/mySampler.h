#pragma once
#include <vector>
#include "myMath.h"

class mySampler
{
public:
	mySampler() : 
	numSamples(25), numSets(83) {}

	mySampler(int _numSamples, int _numSets = 83, std::vector<myPoint> _samples = std::vector<myPoint>(),
		std::vector<int> _sI = std::vector<int>(), unsigned long _count = 0, int _jump = 1) :
		numSamples(_numSamples), numSets(_numSets), samples(_samples),
		shuffledIndices(_sI), count(_count), jump(_jump) {}

	virtual ~mySampler() {}

	virtual void generateSamples() = 0;
	
	void setupShuffledIndices();
	void shuffleSamples();

	myPoint sampleUnitSquare();

protected:
	double randDouble() {
		return rand() / static_cast<double>(RAND_MAX);
	}

	int numSamples; //the number of sample points in a pattern
	int numSets; //the number of sample sets (patterns) stored
	std::vector<myPoint> samples; // sample points on a unit square
	std::vector<int> shuffledIndices; // shuffled samples array indices
	unsigned long count; //the current number of sample points used
	int jump; // random index jump
};