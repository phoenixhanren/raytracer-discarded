#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>



#include "myWorld.h"

int main()
{
	//myWorld w;
	//w.build();
	//myPoint eye(0, 0, 500);
	//myPoint lookat(0, 0, -100);
	//myVector up(0, 1, 0);
	//myPinhole p(eye, lookat, up, 200, 1);
	//p.computeUVW();
	//int* ans = p.renderScene(w);
	//w.renderScene();
	//w.renderPerspective();

	std::cout << "ÇëÊäÈëÂ·¾¶" << std::endl;
	std::string s;
	std::cin >> s;
	myWorld w;
	w.build();
	int*** ans = w.cameraPtr->renderScene(w);
	std::cout << s;
	std::ofstream writer = std::ofstream(s, 'w');
	writer << "P3 " << w.vp.hres << " " << w.vp.vres << " 256 \r\n";
	
	//for (int i = 0; i != w.vp.hres * w.vp.vres * 3 ; ++i)
	//{
	//	//if (w.colors[i] == 255)
	//	//	std::cout << w.colors[i] << "\r\n";
	//	//writer << w.colors[i++] << " " << w.colors[i++] << " " << w.colors[i++] << "\r\n";
	//	//std::cout << i << std::endl;
	//	writer << ans[i] << " ";
	//	i += 1;
	//	writer << ans[i] << " ";
	//	i += 1;
	//	writer << ans[i] << "\r\n";
	//}
	for (int r = 0; r != w.vp.vres; ++r)
	{
		for (int c = 0; c != w.vp.hres; ++c)
		{
			//int x = c;
			//int y = w.vp.vres - r - 1;
			writer << ans[r][c][0] << " " << ans[r][c][1] << " " << ans[r][c][2] << "\r\n";
		}
	}

	writer.flush();
	writer.close();
	
	//myMesh* mesh = new myMesh;
	//std::vector<myMeshTriangle*> triangles;
	//char *fileName = "D:\\cg\\chopper.ply";
	//readPly(fileName, mesh, triangles);
	//computeMeshNormal(mesh, triangles);
	return 0;
}

