/*
 * A PLY file loader
 */

#include <Maoni/MeshLoader.hpp>
#include "../VBOModel.hpp"
#include "plyfile.h"
#include <boost/cstdint.hpp>
#include <stdexcept>
#include <iostream>

static bool _invertFaces = false;

//static void useInvertedFaces() {
//	_invertFaces = true;
//}


// PLY model class
class ModelPLY: public VBOModel
{
public:
	ModelPLY(const char* filename, int myrank, int ranks);
	~ModelPLY();

protected:
	void readVertices(PlyFile* file, const int nVertices);
	void readTriangles(PlyFile* file, const int nFaces);
};

// Load PLY model
ModelPLY::ModelPLY(const char* filename, int myrank, int ranks)
{
	int nPlyElems;
	char** elemNames;
	int fileType;
	float version;
	bool result = false;

	PlyFile* file = ply_open_for_reading(const_cast<char*> (filename),
			&nPlyElems, &elemNames, &fileType, &version);
	if (!file)
		throw std::runtime_error("Unable to open PLY file for reading.");

	BOOST_ASSERT( elemNames != 0 );

	// read in vertices
	for (int i = 0; i < nPlyElems; ++i)
	{
		int nElems;
		int nProps;

		PlyProperty** props = ply_get_element_description(file, elemNames[i],
				&nElems, &nProps);
		BOOST_ASSERT( props != 0 );

		if (equal_strings(elemNames[i], "vertex"))
		{
			readVertices(file, nElems);
		}
		else if (equal_strings(elemNames[i], "face"))
			try
			{
				readTriangles(file, nElems);
				result = true;
			} catch (std::exception& e)
			{
				std::cerr << "Unable to read PLY file, an exception occured:  "
						<< e.what() << std::endl;
				// stop for loop by setting the loop variable to break condition
				// this way resources still get released even on error cases
				i = nPlyElems;
			}

		// free the memory that was allocated by ply_get_element_description
		for (int j = 0; j < nProps; ++j)
			free(props[j]);
		free(props);
	}

	ply_close(file);

	// free the memory that was allocated by ply_open_for_reading
	for (int i = 0; i < nPlyElems; ++i)
		free(elemNames[i]);
	free(elemNames);

	calculate_normals();
	fix_scale();
	generate_vbo();
	setDrawRange(myrank, ranks);
}

/*  Read the vertex and (if available/wanted) color data from the open file.  */
void ModelPLY::readVertices(PlyFile* file, const int nVertices)
{
	// temporary vertex structure for ply loading
	struct _Vertex
	{
		float x;
		float y;
		float z;
		unsigned char r;
		unsigned char g;
		unsigned char b;
	} vertex;

	PlyProperty vertexProps[] = { { "x", PLY_FLOAT, PLY_FLOAT, offsetof(
			_Vertex, x), 0, 0, 0, 0 }, { "y", PLY_FLOAT, PLY_FLOAT, offsetof(
			_Vertex, y), 0, 0, 0, 0 }, { "z", PLY_FLOAT, PLY_FLOAT, offsetof(
			_Vertex, z), 0, 0, 0, 0 }, { "red", PLY_UCHAR, PLY_UCHAR, offsetof(
			_Vertex, r), 0, 0, 0, 0 }, { "green", PLY_UCHAR, PLY_UCHAR,
			offsetof(_Vertex, g), 0, 0, 0, 0 }, { "blue", PLY_UCHAR, PLY_UCHAR,
			offsetof(_Vertex, b), 0, 0, 0, 0 } };

	// use all 6 properties when reading colors, only the first 3 otherwise
	for (int i = 0; i < 6; ++i)
		ply_get_property(file, "vertex", &vertexProps[i]);

	reserve_vertices(nVertices);

	// read in the vertices
	for (int i = 0; i < nVertices; ++i)
	{
		ply_get_element(file, static_cast<void*> (&vertex));
		add_vertex(Vertex(Vec3(vertex.x, vertex.y, vertex.z), Vec3(),
				Color(vertex.r / 255.f, vertex.g / 255.f, vertex.b / 255.f, 0),
				Vec2()));
	}
}

/*  Read the index data from the open file.  */
void ModelPLY::readTriangles(PlyFile* file, const int nFaces)
{
	// temporary face structure for ply loading
	struct _Face
	{
		unsigned char nVertices;
		int* vertices;
	} face;

	PlyProperty faceProps[] = { { "vertex_indices", PLY_INT, PLY_INT, offsetof(
			_Face, vertices), 1, PLY_UCHAR, PLY_UCHAR, offsetof(_Face,
			nVertices) } };

	ply_get_property(file, "face", &faceProps[0]);

	reserve_triangles(nFaces);

	// read in the faces, asserting that they are only triangles
	boost::uint8_t ind1 = _invertFaces ? 2 : 0;
	boost::uint8_t ind3 = _invertFaces ? 0 : 2;
	for (int i = 0; i < nFaces; ++i)
	{
		ply_get_element(file, static_cast<void*> (&face));
		BOOST_ASSERT(face.vertices != 0);
		if (face.nVertices != 3)
		{
			free(face.vertices);
			throw std::runtime_error("Error reading PLY file. Encountered a "
				"face which does not have three vertices.");
		}
		add_triangle(face.vertices[ind1], face.vertices[1],
				face.vertices[ind3]);

		// free the memory that was allocated by ply_get_element
		free(face.vertices);
	}
}

MESH_LOADER(ply, Stanford PLY)
{
	model.reset(new ModelPLY(filename, myrank, ranks));
}
