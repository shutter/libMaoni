/*
 * A 3DS file loader
 */

#include <Maoni/MeshLoader.hpp>

#include <GL/glew.h>
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>

#include <stdexcept>
#include <iostream>
#include <cstring>

// 3DS model class
class CModel3DS: public Model
{
public:
	CModel3DS(std::string filename);
	~CModel3DS();

	void draw() const;
	void CreateVBO();

protected:
	void GetFaces();
	unsigned int m_TotalFaces;
	Lib3dsFile * m_model;
	GLuint m_VertexVBO, m_NormalVBO;
	Lib3dsVector offset;
	float factor;
};

// Load 3DS model
CModel3DS::CModel3DS(std::string filename)
{
	m_TotalFaces = 0;

	m_model = lib3ds_file_load(filename.c_str());
	// If loading the model failed, we throw an exception
	if (!m_model)
	{
		throw std::runtime_error("Loading file failed");
	}

	// find resize factor
	Lib3dsVector min;
	Lib3dsVector max;
	lib3ds_file_bounding_box_of_objects(m_model, true, false, false, min, max);

	std::cout << "max: " << max[0] << " " << max[1] << " " << max[2]
			<< std::endl;
	std::cout << "min: " << min[0] << " " << min[1] << " " << min[2]
			<< std::endl;

	// find largest dimension and determine scale factor
	factor = 0.0f;
	for (size_t i = 0; i < 3; ++i)
		factor = std::max(factor, max[i] - min[i]);

	factor = 2.f / factor;
	std::cout << "resize factor: " << factor << std::endl;

	// determine scale offset

	for (size_t i = 0; i < 3; ++i)
		offset[i] = (min[i] + max[i]) * 0.5f;

	std::cout << "offset: " << offset[0] << " " << offset[1] << " "
			<< offset[2] << std::endl;

	GetFaces();
	CreateVBO();
}

// Destructor
CModel3DS::~CModel3DS()
{
	glDeleteBuffers(1, &m_VertexVBO);
	glDeleteBuffers(1, &m_NormalVBO);

	if (m_model != NULL)
	{
		lib3ds_file_free(m_model);
	}
}

// Copy vertices and normals to the memory of the GPU
void CModel3DS::CreateVBO()
{
	assert(m_model != NULL);

	// Calculate the number of faces we have in total
	GetFaces();

	// Allocate memory for our vertices and normals
	Lib3dsVector * vertices = new Lib3dsVector[m_TotalFaces * 3];
	Lib3dsVector * normals = new Lib3dsVector[m_TotalFaces * 3];

	Lib3dsMesh * mesh;
	unsigned int FinishedFaces = 0;
	// Loop through all the meshes
	for (mesh = m_model->meshes; mesh != NULL; mesh = mesh->next)
	{
		lib3ds_mesh_calculate_normals(mesh, &normals[FinishedFaces * 3]);
		// Loop through every face
		for (unsigned int cur_face = 0; cur_face < mesh->faces; cur_face++)
		{
			Lib3dsFace * face = &mesh->faceL[cur_face];
			for (unsigned int i = 0; i < 3; ++i)
			{
				Lib3dsVector tmp;
				for (unsigned int j = 0; j < 3; ++j)
				{
					tmp[j] = (mesh->pointL[face->points[i]].pos[j] - offset[j])
							* factor;
				}
				memcpy(&vertices[FinishedFaces * 3 + i], tmp,
						sizeof(Lib3dsVector));
			}
			FinishedFaces++;
		}
	}

	// Generate a Vertex Buffer Object and store it with our vertices
	glGenBuffers(1, &m_VertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces,
			vertices, GL_STATIC_DRAW);

	// Generate another Vertex Buffer Object and store the normals in it
	glGenBuffers(1, &m_NormalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Lib3dsVector) * 3 * m_TotalFaces,
			normals, GL_STATIC_DRAW);

	// Clean up our allocated memory
	delete[] vertices;
	delete[] normals;

	// We no longer need lib3ds
	lib3ds_file_free(m_model);
	m_model = NULL;
}

// Count the total number of faces this model has
void CModel3DS::GetFaces()
{
	assert(m_model != NULL);

	m_TotalFaces = 0;
	Lib3dsMesh * mesh;
	// Loop through every mesh
	for (mesh = m_model->meshes; mesh != NULL; mesh = mesh->next)
	{
		// Add the number of faces this mesh has to the total faces
		m_TotalFaces += mesh->faces;
	}
}

// Render the model using Vertex Buffer Objects
void CModel3DS::draw() const
{
	assert(m_TotalFaces != 0);

	// Enable vertex and normal arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Bind the vbo with the normals
	glBindBuffer(GL_ARRAY_BUFFER, m_NormalVBO);
	// The pointer for the normals is NULL which means that OpenGL will use the currently bound vbo
	glNormalPointer(GL_FLOAT, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexVBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	// Render the triangles
	glDrawArrays(GL_TRIANGLES, 0, m_TotalFaces * 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

MESH_LOADER(3ds, 3D Studio Max Model)
{
	model.reset(new CModel3DS(filename));
}
