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
		glColor4fv(vertices[indices[i]].color.array);
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

void Model::reserve_quads(std::size_t number)
{
	indices.reserve(number * 3 * 2);
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

void Model::add_quad(std::size_t a, std::size_t b, std::size_t c, std::size_t d)
{
	indices.push_back(a);
	indices.push_back(b);
	indices.push_back(c);

	indices.push_back(c);
	indices.push_back(d);
	indices.push_back(a);
}

void Model::calculate_normals()
{
	Vector3 triangleNormal;
	std::size_t i0, i1, i2;

	// iterate over all triangles and add their normals to adjacent vertices
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		i0 = indices[i + 0];
		i1 = indices[i + 1];
		i2 = indices[i + 2];

		triangleNormal.compute_normal(vertices[i0].position.array,
				vertices[i1].position.array, vertices[i2].position.array);

		vertices[i0].normal += triangleNormal;
		vertices[i1].normal += triangleNormal;
		vertices[i2].normal += triangleNormal;
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
