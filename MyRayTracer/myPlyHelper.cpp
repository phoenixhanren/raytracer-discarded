#pragma once
#include <iostream>
#include "ply.h"
#include "myPlyHelper.h"

void readPly(char *file_name, myMesh *mesh_ptr, std::vector<myMeshTriangle *> &objects,
	myMatrix scale, myMatrix move)
{

	typedef struct Vertex {
		float x, y, z;      // space coordinates       
	} Vertex;

	// Face definition. This is the same for all files but is placed here to keep all the definitions together

	typedef struct Face {
		unsigned char nverts;    // number of vertex indices in list
		int* verts;              // vertex index list 
	} Face;

	// list of property information for a vertex
	// this varies depending on what you are reading from the file

	PlyProperty vert_props[] = {
		{ "x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0 },
		{ "y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0 },
		{ "z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0 }
	};

	// list of property information for a face. 
	// there is a single property, which is a list
	// this is the same for all files

	PlyProperty face_props[] = {
		{ "vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
		1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts) }
	};

	// local variables

	int 			i, j;
	PlyFile*		ply;
	int 			nelems;		// number of element types: 2 in our case - vertices and faces
	char**			elist;
	int 			file_type;
	float 			version;
	int 			nprops;		// number of properties each element has
	int 			num_elems;	// number of each type of element: number of vertices or number of faces
	PlyProperty**	plist;
	Vertex**		vlist;
	Face**			flist;
	char*			elem_name;
	int				num_comments;
	char**			comments;
	int 			num_obj_info;
	char**			obj_info;


	// open a ply file for reading

	ply = ply_open_for_reading(file_name, &nelems, &elist, &file_type, &version);

	// print what we found out about the file

	printf("version %f\n", version);
	printf("type %d\n", file_type);

	// go through each kind of element that we learned is in the file and read them 

	for (i = 0; i < nelems; i++) {  // there are only two elements in our files: vertices and faces
									// get the description of the first element 

		elem_name = elist[i];
		plist = ply_get_element_description(ply, elem_name, &num_elems, &nprops);

		// print the name of the element, for debugging

		std::cout << "element name  " << elem_name << "  num elements = " << num_elems << "  num properties =  " << nprops << std::endl;

		// if we're on vertex elements, read in the properties

		if (equal_strings("vertex", elem_name)) {
			// set up for getting vertex elements
			// the three properties are the vertex coordinates

			ply_get_property(ply, elem_name, &vert_props[0]);
			ply_get_property(ply, elem_name, &vert_props[1]);
			ply_get_property(ply, elem_name, &vert_props[2]);

			// reserve mesh elements

			mesh_ptr->numVertices = num_elems;
			mesh_ptr->vertices.reserve(num_elems);

			// grab all the vertex elements
			//myMatrix trans(1000, 1000, 1000, 's');
			for (j = 0; j < num_elems; j++) {
				Vertex* vertex_ptr = new Vertex;

				// grab an element from the file
				
				ply_get_element(ply, (void *)vertex_ptr);
				myPoint temp(vertex_ptr->x, vertex_ptr->y, vertex_ptr->z);
				//std::cout << temp;
				scale.transform(temp);
				move.transform(temp);
				
				//std::cout << temp;
				
				//std::cout << temp;
				//trans.transform(temp);
				//std::cout << temp;
				//std::cout << "============\n";
				//mesh_ptr->vertices.push_back(myPoint(vertex_ptr->x, vertex_ptr->y, vertex_ptr->z));
				mesh_ptr->vertices.push_back(temp);
				delete vertex_ptr;
			}
		}

		// if we're on face elements, read them in 

		if (equal_strings("face", elem_name)) {
			// set up for getting face elements

			ply_get_property(ply, elem_name, &face_props[0]);   // only one property - a list

			mesh_ptr->numTriangles = num_elems;
			//objects.reserve(num_elems);  // triangles will be stored in Compound::objects

			// the following code stores the face numbers that are shared by each vertex

			mesh_ptr->vertexFaces.reserve(mesh_ptr->numVertices);
			vector<int> faceList;

			for (j = 0; j < mesh_ptr->numVertices; j++)
				mesh_ptr->vertexFaces.push_back(faceList); // store empty lists so that we can use the [] notation below

														   // grab all the face elements

			int count = 0; // the number of faces read

			for (j = 0; j < num_elems; j++) {
				// grab an element from the file 

				Face* face_ptr = new Face;

				ply_get_element(ply, (void *)face_ptr);

				// construct a mesh triangle of the specified type



				myMeshTriangle* triangle_ptr = new myMeshTriangle(mesh_ptr, face_ptr->verts[0], face_ptr->verts[1], face_ptr->verts[2]);
				//triangle_ptr->computeNormal(reverse_normal); 	// the "flat triangle" normal is used to compute the average normal at each mesh vertex
				objects.push_back(triangle_ptr); 				// it's quicker to do it once here, than have to do it on average 6 times in compute_mesh_normals

																// the following code stores a list of all faces that share a vertex
																// it's used for computing the average normal at each vertex in order(num_vertices) time

				mesh_ptr->vertexFaces[face_ptr->verts[0]].push_back(count);
				mesh_ptr->vertexFaces[face_ptr->verts[1]].push_back(count);
				mesh_ptr->vertexFaces[face_ptr->verts[2]].push_back(count);
				count++;

			}

		}

		// print out the properties we got, for debugging

		for (j = 0; j < nprops; j++)
			printf("property %s\n", plist[j]->name);

	}  // end of for (i = 0; i < nelems; i++) 


	   // grab and print out the comments in the file

	comments = ply_get_comments(ply, &num_comments);

	for (i = 0; i < num_comments; i++)
		printf("comment = '%s'\n", comments[i]);

	// grab and print out the object information

	obj_info = ply_get_obj_info(ply, &num_obj_info);

	for (i = 0; i < num_obj_info; i++)
		printf("obj_info = '%s'\n", obj_info[i]);

	// close the ply file 

	ply_close(ply);
}

void computeMeshNormal(myMesh *mesh_ptr, std::vector<myMeshTriangle *> &objects)
{
	mesh_ptr->normals.reserve(mesh_ptr->numVertices);

	for (int index = 0; index < mesh_ptr->numVertices; index++) {   // for each vertex
		myNormal normal;    // is zero at this point	

		for (int j = 0; j < mesh_ptr->vertexFaces[index].size(); j++)
			normal += objects[mesh_ptr->vertexFaces[index][j]]->getNormal();

		// The following code attempts to avoid (nan, nan, nan) normalised normals when all components = 0

		if (normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0)
			normal.y = 1.0;
		else
			normal = noralize(normal);

		mesh_ptr->normals.push_back(normal);
	}

	// erase the vertex_faces arrays because we have now finished with them

	for (int index = 0; index < mesh_ptr->numVertices; index++)
		for (int j = 0; j < mesh_ptr->vertexFaces[index].size(); j++)
			mesh_ptr->vertexFaces[index].erase(mesh_ptr->vertexFaces[index].begin(), mesh_ptr->vertexFaces[index].end());

	mesh_ptr->vertexFaces.erase(mesh_ptr->vertexFaces.begin(), mesh_ptr->vertexFaces.end());

	std::cout << "finished constructing normals" << std::endl;
}