/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <GL/glew.h>
#include <Maoni/Model.hpp>
#include <boost/array.hpp>
#include <iostream>

#include <boost/la/all.hpp>
using namespace boost::la;

GLuint vboVertexBuffer; // ID of VBO for vertices
GLuint vboNormalBuffer; // ID of VBO normals
GLuint vboColorBuffer; // ID of VBO colors
GLuint vboTexCoordBuffer; // ID of VBO texCoords
GLuint vboIndexBuffer; // ID of VBO faces

void Model::draw() const
{
	if (!vbo_loaded)
	{
		std::cout << "no vbo!" << std::endl;
		glBegin(GL_TRIANGLES);
		for (size_t i = start_; i < start_ + count_; i++)
		{
			glColor4fv(vertices[indices[i]].color);
			glTexCoord2fv(vertices[indices[i]].texcoord);
			glNormal3fv(vertices[indices[i]].normal);
			glVertex3fv(vertices[indices[i]].position);
		}
		glEnd();
	}
	else
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, vboVertexBuffer);
		glVertexPointer(3, GL_FLOAT, 0, (char *) NULL); // Set The Vertex Pointer To The Vertex Buffer

		glBindBuffer(GL_ARRAY_BUFFER, vboNormalBuffer);
		glNormalPointer(GL_FLOAT, 0, (char *) NULL); // Set The Normal Pointer To The Normal Buffer

		glBindBuffer(GL_ARRAY_BUFFER, vboColorBuffer);
		glColorPointer(4, GL_FLOAT, 0, (char *) NULL); // Set The Color Pointer To The Color Buffer

		glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, (char *) NULL); // Set The TexCoord Pointer To The TexCoord Buffer

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndexBuffer);

		glDrawRangeElements(GL_TRIANGLES, start_, end_, count_,
				GL_UNSIGNED_INT, startindex);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void Model::clear()
{
	vertices.clear();
	indices.clear();
	vbo_loaded = false;
}

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
		vertices[i].normal = Vec3(0, 0, 0);

	// iterate over all triangles and add their normals to adjacent vertices
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		i0 = indices[i + 0];
		i1 = indices[i + 1];
		i2 = indices[i + 2];

		Vec3 const& p1 = vertices[i0].position;
		Vec3 const& p2 = vertices[i1].position;
		Vec3 const& p3 = vertices[i2].position;
		Vec3 normal = cross(p2 - p1, p3 - p1);

		vertices[i0].normal = vertices[i0].normal + normal;
		vertices[i1].normal = vertices[i1].normal + normal;
		vertices[i2].normal = vertices[i2].normal + normal;
	}

	// normalize all the normals
	for (size_t i = 0; i < vertices.size(); ++i)
		vertices[i].normal /= magnitude(vertices[i].normal);
}

void Model::fix_scale()
{
	Vec3 lower_left = vertices[0].position;
	Vec3 upper_right = vertices[0].position;

	// calculate bounding box
	for (size_t v = 1; v < vertices.size(); ++v)
	{
		Vec3& pos = vertices[v].position;
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
	Vec3 offset;
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

void Model::generate_vbo()
{
	vsize = vertices.size();
	isize = indices.size();
	std::cout << "vertices: " << vsize << " indices: " << isize << std::endl;

	GLfloat* vbo_vertices = new GLfloat[vsize * 3];
	GLfloat* vbo_normals = new GLfloat[vsize * 3];
	GLfloat* vbo_colors = new GLfloat[vsize * 4];
	GLfloat* vbo_texCoords = new GLfloat[vsize * 2];
	GLuint* ibo_list = new GLuint[isize];

	for (size_t i = 0; i < vsize; ++i)
	{

		vbo_vertices[i * 3] = vertices[i].position[0];
		vbo_vertices[i * 3 + 1] = vertices[i].position[1];
		vbo_vertices[i * 3 + 2] = vertices[i].position[2];
		vbo_normals[i * 3] = vertices[i].normal[0];
		vbo_normals[i * 3 + 1] = vertices[i].normal[1];
		vbo_normals[i * 3 + 2] = vertices[i].normal[2];
		vbo_colors[i * 4] = vertices[i].color[0];
		vbo_colors[i * 4 + 1] = vertices[i].color[1];
		vbo_colors[i * 4 + 2] = vertices[i].color[2];
		vbo_colors[i * 4 + 3] = vertices[i].color[3];
		vbo_texCoords[i * 2] = vertices[i].texcoord[0];
		vbo_texCoords[i * 2 + 1] = vertices[i].texcoord[1];
		/*		std::cout << vbo_vertices[i * 3] << " " << vbo_vertices[i * 3 + 1]
		 << " " << vbo_vertices[i * 3 + 2] << " " << vbo_normals[i * 3]
		 << " " << vbo_normals[i * 3 + 1] << " " << vbo_normals[i * 3
		 + 2] << " " << vbo_colors[i * 4] << " "
		 << vbo_colors[i * 4 + 1] << " " << vbo_colors[i * 4 + 2] << " "
		 << vbo_colors[i * 4 + 3] << " " << vbo_texCoords[i * 2] << " "
		 << vbo_texCoords[i * 2 + 1] << std::endl;*/
	}

	for (size_t i = 0; i < isize; ++i)
	{
		ibo_list[i] = indices[i];
		// std::cout << ibo_list[i] << " ";
	}

	glGenBuffers(1, &vboIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(GLuint), ibo_list,
			GL_STATIC_DRAW);

	glGenBuffers(1, &vboVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vsize * 3 * sizeof(GLfloat), vbo_vertices,
			GL_STATIC_DRAW);

	glGenBuffers(1, &vboNormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, vsize * 3 * sizeof(GLfloat), vbo_normals,
			GL_STATIC_DRAW);

	glGenBuffers(1, &vboColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vboColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, vsize * 4 * sizeof(GLfloat), vbo_colors,
			GL_STATIC_DRAW);

	glGenBuffers(1, &vboTexCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, vsize * 2 * sizeof(GLfloat), vbo_texCoords,
			GL_STATIC_DRAW);

	delete[] ibo_list;
	delete[] vbo_vertices;
	delete[] vbo_normals;
	delete[] vbo_colors;
	delete[] vbo_texCoords;

	start_ = 0;
	end_ = isize;
	count_ = isize;
	vbo_loaded = true;
}

void Model::setStartVertex(unsigned int start)
{
	start_ = start;
}
void Model::setEndVertex(unsigned int end)
{
	if (end > end_)
	{
		end_ = isize;
		count_ = end_ - start_;
	}
	else
	{
		count_ = end - start_;
		end_ = isize;//end;
	}
}

void Model::calcDrawRange(unsigned int myrank, unsigned int ranks)
{
	myrank_ = myrank;
	ranks_ = ranks;
	int frag = isize/3/ranks;
	setStartVertex(myrank * frag * 3);
	setEndVertex((myrank + 1) * (frag + 1) * 3);
	startindex = (char*)NULL + (myrank * frag * 3 * sizeof(unsigned int));
	std::cout << "rank" << myrank << " - start: " << start_ << ", end: " << end_ << ", count: " << count_ << std::endl;
}
