/*
 * Mesh.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: shutter
 */

#include <GL/glew.h>
#include <Maoni/Model.hpp>

void Model::draw() const
{
	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < indices.size(); i++)
	{
		glColor4fv(vertices[indices[i]].color);
		glTexCoord2fv(vertices[indices[i]].texcoord.array);
		glNormal3fv(vertices[indices[i]].normal.array);
		glVertex3fv(vertices[indices[i]].position.array);
	}

	glEnd();
}

void Model::clear()
{
	vertices.clear();
	indices.clear();

	bounding_box[0] = Vector3(0.0f);
	bounding_box[1] = Vector3(0.0f);
}

//!
bool Model::empty() const
{
	return indices.empty();
}

void Model::reserve_vertices(std::size_t number)
{
	vertices.reserve(number);
}

void Model::reserve_triangles(std::size_t number)
{
	indices.reserve(number * 3);
}

void Model::add_vertex(Vertex const& vertex)
{
	vertices.push_back(vertex);
}

void Model::add_triangle(std::size_t a, std::size_t b, std::size_t c)
{
	indices.push_back(a);
	indices.push_back(b);
	indices.push_back(c);
}

void Model::calculate_normals()
{
	std::size_t i0, i1, i2;

	for (size_t i = 0; i < vertices.size(); ++i)
		vertices[i].normal = Vector3(0,0,0);

	// iterate over all triangles and add their normals to adjacent vertices
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		i0 = indices[i + 0];
		i1 = indices[i + 1];
		i2 = indices[i + 2];

		Vector3 const& p1 = vertices[i0].position;
		Vector3 const& p2 = vertices[i1].position;
		Vector3 const& p3 = vertices[i2].position;

		Vector3 v1 = p2 - p1;
		Vector3 v2 = p3 - p1;
		Vector3 normal = Vector3(v1.z()*v2.z()-v1.z()*v2.y(),v1.z()*v2.x()-v1.x()*v2.z(),v1.x()*v2.y()-v1.y()*v2.x());

		vertices[i0].normal += normal;
		vertices[i1].normal += normal;
		vertices[i2].normal += normal;
	}

	// normalize all the normals
	for (size_t i = 0; i < vertices.size(); ++i)
		vertices[i].normal.normalize();
}

/* Calculate the bounding box of the current vertex data. */
void Model::calculateBoundingBox()
{
	bounding_box[0] = vertices[0].position.array;
	bounding_box[1] = vertices[0].position.array;
	for (size_t v = 1; v < vertices.size(); ++v)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			bounding_box[0][i] = std::min(bounding_box[0][i],
					vertices[v].position[i]);
			bounding_box[1][i] = std::max(bounding_box[1][i],
					vertices[v].position[i]);
		}
	}
}

/* Scales the data to be within +- baseSize/2 (default 2.0) coordinates. */
void Model::fix_scale()
{
	// calculate bounding box if not yet done
	calculateBoundingBox();

	// find largest dimension and determine scale factor
	float factor = 0.0f;
	for (size_t i = 0; i < 3; ++i)
		factor = std::max(factor, bounding_box[1][i] - bounding_box[0][i]);

	factor = 2.0 / factor;

	// determine scale offset
	Vector3 offset;
	for (size_t i = 0; i < 3; ++i)
		offset[i] = (bounding_box[0][i] + bounding_box[1][i]) * 0.5f;

	// scale the data
	for (size_t v = 0; v < vertices.size(); ++v)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			vertices[v].position[i] -= offset[i];
			vertices[v].position[i] *= factor;
		}
	}

	// scale the bounding box
	for (size_t v = 0; v < 2; ++v)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			bounding_box[v][i] -= offset[i];
			bounding_box[v][i] *= factor;
		}
	}
}
