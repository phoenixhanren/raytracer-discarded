#include "myCamera.h"

void myCamera::computeUVW()
{
	w = eye - lookat;
	w = normalize(w);
	//w = temp;
	//u = cross(up, w);
	u = cross(w, up);
	u = normalize(u);
	v = cross(u, w);
	//v = cross(w, u);
	//v = normalize(v);

	if (eye.x == lookat.x && eye.z == lookat.z)
	{
		if (eye.y > lookat.y)
		{
			u = myVector(0, 0, 1);
			v = myVector(1, 0, 0);
			w = myVector(0, 1, 0);
		}

		else if (eye.y < lookat.y)
		{
			u = myVector(1, 0, 0);
			v = myVector(0, 0, 1);
			w = myVector(0, -1, 0);
		}
	}
	std::cout << u << v << w << std::endl;
//	std::cout << "123";
}
