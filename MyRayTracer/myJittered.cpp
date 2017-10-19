#include "myJittered.h"

void myJittered::generateSamples()
{
	int n = static_cast<int>(sqrt(numSamples));

	for (int p = 0; p < numSets; ++p)
	{
		for (int j = 0; j < n; ++j)
		{
			for (int k = 0; k < n; ++k)
			{
				myPoint sp((k + randDouble()) / n, (j + randDouble()) / n, 0);
				samples.push_back(sp);
			}
		}
	}
}
