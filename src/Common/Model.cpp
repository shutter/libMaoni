/*
 * Mesh.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: shutter
 */

#include <GL/glew.h>
#include <Maoni/Model.hpp>
#include <boost/array.hpp>
#include <iostream>

#include <boost/la/all.hpp>
using namespace boost::la;

void Model::draw() const
{
	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < indices.size(); i++)
	{
		glColor4fv(vertices[indices[i]].color);
		glTexCoord2fv(vertices[indices[i]].texcoord);
		glNormal3fv(vertices[indices[i]].normal);
		glVertex3fv(vertices[indices[i]].position);
	}

	glEnd();
}

void Model::clear()
{
	vertices.clear();
	indices.clear();
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
		vertices[i].normal = Vector3(0, 0, 0);

	// iterate over all triangles and add their normals to adjacent vertices
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		i0 = indices[i + 0];
		i1 = indices[i + 1];
		i2 = indices[i + 2];

		Vector3 const& p1 = vertices[i0].position;
		Vector3 const& p2 = vertices[i1].position;
		Vector3 const& p3 = vertices[i2].position;
		Vector3 normal = cross(p2 - p1, p3 - p1);

		vertices[i0].normal = vertices[i0].normal + normal;
		vertices[i1].normal = vertices[i1].normal + normal;
		vertices[i2].normal = vertices[i2].normal + normal;
	}

	// normalize all the normals
	for (size_t i = 0; i < vertices.size(); ++i)
		vertices[i].normal /= magnitude(vertices[i].normal);
}

/* Scales the data to be within +- baseSize/2 (default 2.0) coordinates. */
void Model::fix_scale()
{
	Vector3 lower_left = vertices[0].position;
	Vector3 upper_right = vertices[0].position;

	// calculate bounding box
	for (size_t v = 1; v < vertices.size(); ++v)
	{
		Vector3& pos = vertices[v].position;
		for (size_t i = 0; i < 3; ++i)
		{
			lower_left.data[i] = std::min(lower_left[i], pos[i]);
			upper_right.data[i] = std::max(upper_right[i], pos[i]);
		}
	}

	std::clog << std::flush;
	std::clog << "lower_left = (" << (lower_left | X) << ", " //
			<< (lower_left | Y) << ", " << (lower_left | Z) << ")\n";
	std::clog << "upper_right = (" << (upper_right | X) << ", " //
			<< (upper_right | Y) << ", " << (upper_right | Z) << ")\n";

	// find largest dimension and determine scale factor
	float factor = 0.0f;
	for (size_t i = 0; i < 3; ++i)
		factor = std::max(factor, upper_right[i] - lower_left[i]);

	factor = 2.f / factor;
	std::clog << "scale factor = " << factor << "\n";

	// determine scale offset
	Vector3 offset;
	for (size_t i = 0; i < 3; ++i)
		offset.data[i] = (lower_left[i] + upper_right[i]) * 0.5f;

	std::clog << "offset = (" << (offset | X) << ", " //
			<< (offset | Y) << ", " << (offset | Z) << ")" << std::endl;

	// scale the data
	for (size_t v = 0; v < vertices.size(); ++v)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			vertices[v].position.data[i] -= offset[i];
			vertices[v].position.data[i] *= factor;
		}
	}
}
