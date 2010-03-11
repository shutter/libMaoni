/*
 * Mesh.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: shutter
 */

#include <GL/glew.h>
#include <Maoni/Model.hpp>
#include <Maoni/Teaset.h>

static void qglviewer_spiral()
{
	const float nbSteps = 200.0;

	glBegin(GL_QUAD_STRIP);

	for (int i = 0; i < nbSteps; ++i)
	{
		const float ratio = i / nbSteps;
		const float angle = 21.0 * ratio;
		const float c = cos(angle);
		const float s = sin(angle);
		const float r1 = 1.0 - 0.8f * ratio;
		const float r2 = 0.8f - 0.8f * ratio;
		const float alt = ratio - 0.5f;
		const float nor = 0.5f;
		const float up = sqrt(1.0 - nor * nor);
		glColor3f(1.0 - ratio, 0.2f, ratio);
		glNormal3f(nor * c, up, nor * s);
		glVertex3f(r1 * c, alt, r1 * s);
		glVertex3f(r2 * c, alt + 0.05f, r2 * s);
	}

	glEnd();
}

void Model::draw() const
{
	switch (bezier_mesh)
	{
	case teacup:
		solid_teacup(1.f);
		return;
	case teapot:
		solid_teapot(1.f);
		return;
	case teaspoon:
		solid_teaspoon(1.f);
		return;
	case spiral:
		qglviewer_spiral();
		return;
	default:
		break;
	}

	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < indices.size(); i++)
	{
		glColor4fv(vertices[indices[i]].color);
		glTexCoord2fv(vertices[indices[i]].texcoord);
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
