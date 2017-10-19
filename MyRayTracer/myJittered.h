#pragma once
#include "mySampler.h"

class myJittered : public mySampler
{
public:
	myJittered() :
		mySampler() {
		generateSamples();
	}

	myJittered(int numSamples) :
		mySampler(numSamples) {
		generateSamples();
	}

	virtual ~myJittered() override {}

private:
	virtual void generateSamples() override;
};