/*
 * A STL file loader
 */

#include <Maoni/MeshLoader.hpp>
#include "../VBOModel.hpp"
#include <stdexcept>
#include <iostream>

#include "stla_io.h"

// STL model class
class ModelSTL: public VBOModel
{
public:
	ModelSTL(const char* filename, int myrank, int ranks);
	~ModelSTL();

protected:
};

// Load STL model
ModelSTL::ModelSTL(const char* filename, int myrank, int ranks)
{
	// check if correct ascii stl file
	if (stla_check(filename)) {
		std::cout << "  The file \"" << filename
				<< "\" seems to be a legal ASCII STL file." << std::endl;
	} else {
		throw std::runtime_error("The file does NOT seem to be a legal ASCII STL file.");
	}

	// print file stats
	int face_num;
	int node_num;
	int solid_num;
	int text_num;

	stla_size(filename, &solid_num, &node_num, &face_num, &text_num);
	stla_size_print(filename, solid_num, node_num, face_num, text_num);

	// read file into mesh
	bool error;
	int *face_node;
	double *face_normal;
	double *node_xyz;

	face_node = new int[3 * face_num];
	face_normal = new double[3 * face_num];
	node_xyz = new double[3 * node_num];

	error = stla_read(filename, node_num, face_num, node_xyz, face_node,
			face_normal);

	if (error)
		throw std::runtime_error("An error occured while reading stl file.");

	// copy vertices
	for (int i = 0; i < node_num; i++)
	{
		add_vertex(Vertex(Vec3(node_xyz[i * 3], node_xyz[i * 3 + 1],
				node_xyz[i * 3 + 2]), Vec3(face_normal[i * 3], face_normal[i
				* 3 + 1], face_normal[i * 3 + 2]), Color(), Vec2()));
	}

	// copy nodes to triangles
	for (int i = 0; i < face_num; i++)
	{
		add_triangle(face_node[i * 3], face_node[i * 3 + 1], face_node[i
				* 3 + 2]);
	}

	delete[] face_node;
	delete[] face_normal;
	delete[] node_xyz;

	setDrawRange(myrank, ranks);
	calculate_normals();
	fix_scale();
	generate_vbo();
}

MESH_LOADER(stl, StereoLithography)
{
	model.reset(new ModelSTL(filename, myrank, ranks));
}
