#include "myPinhole.h"
#include "myWorld.h"
int*** myPinhole::renderScene(myWorld & w)
{
	myRGBColor L;
	myViewPlane& vp = w.vp;
	myRay ray;

	myPoint sp; //sample point in [0, 1] * [0, 1]
	myPoint pp; //sample point on a pixel

	vp.s /= zoom;
	ray.o = eye;
	int ***colors = new int**[vp.hres];
	for (int i = 0; i != vp.hres; ++i)
	{
		colors[i] = new int*[vp.vres];
		for (int j = 0; j != vp.vres; ++j)
		{
			colors[i][j] = new int[3];
		}
	}

	//int index = 0;
	double sum = vp.vres * vp.hres;
	for (int r = 0; r < vp.vres; ++r)
	{
		for (int c = 0; c < vp.hres; ++c)
		{
			L = myRGBColor(0, 0, 0);

			for (int j = 0; j < vp.numSamples; j++)
			{
				//std::cerr << (r * vp.hres + c) / sum * 100 << std::endl;
				sp = vp.sampler->sampleUnitSquare();
				//std::cout << "(" << sp.x << ", " << sp.y << ")\n";
				pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
				pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
				ray.dir = rayDirecton(pp);
				L += w.tracerPtr->traceRay(ray, 0);
			}
			std::cout << "\r" << "                           ";
			L /= vp.numSamples;
			maxToOne1(L);
			
			//colors[index++] = static_cast<int>(L.r * 255.0);
			//colors[index++] = static_cast<int>(L.g * 255.0);
			//colors[index++] = static_cast<int>(L.b * 255.0);
			//int x = c;
			//int y = vp.vres - r - 1;
			int x = vp.vres - r - 1;
			int y = vp.hres - c - 1;
			//std::cout << "r: " << r << " c: " << c << "\r\n";
			colors[x][y][0] = static_cast<int>(L.r * 255.0);
			colors[x][y][1] = static_cast<int>(L.g * 255.0);
			colors[x][y][2] = static_cast<int>(L.b * 255.0);
			
			std::cout << "\r" << ((r * vp.vres + c) + 1) / static_cast<double>(vp.hres * vp.vres) * 100.0
				<< "%";
		}

	}
	return colors;
}

void myPinhole::maxToOne1(myRGBColor & pixelColor)
{
	double maxValue = pixelColor.r;
	if (maxValue < pixelColor.g)
		maxValue = pixelColor.g;
	if (maxValue < pixelColor.b)
		maxValue = pixelColor.b;
	if (maxValue > 1.0)
		//std::cout << "233333333333" << std::endl;
		pixelColor =  myRGBColor(pixelColor.r / maxValue, pixelColor.g / maxValue,
			pixelColor.b / maxValue);

}


