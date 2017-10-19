#include "mySampler.h"

void mySampler::setupShuffledIndices()
{
}

void mySampler::shuffleSamples()
{
}

myPoint mySampler::sampleUnitSquare()
{
	return samples[count++ % (numSamples * numSets)];
}
