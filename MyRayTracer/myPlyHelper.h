#pragma once
#include <iostream>
#include "ply.h"
#include "myMesh.h"
#include "myMath.h"
#include "myMeshTriangle.h"

void readPly(char *file_name, myMesh *mesh_ptr, std::vector<myMeshTriangle *> &objects, 
	myMatrix scale, myMatrix move);

void computeMeshNormal(myMesh *mesh_ptr, std::vector<myMeshTriangle *> &objects);
