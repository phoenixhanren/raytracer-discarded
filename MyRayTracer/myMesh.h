#pragma once
#include <vector>
#include "myMath.h"


using std::vector;

class myMesh
{
public:
	vector<myPoint> vertices;
	
	vector<myNormal> normals;
	
	vector<vector<int>> vertexFaces; // the triangles shared by each vertex

	int numVertices;
	int numTriangles;

	myMesh();

	~myMesh() {}

};