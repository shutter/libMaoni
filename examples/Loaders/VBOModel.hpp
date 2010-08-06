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

#ifndef MAONI_VBO_MODEL_HPP
#define MAONI_VBO_MODEL_HPP

#include <vector>
#include <Maoni.hpp>

//! The VBOModel class
/*!
 The VBOModel class is libMaoni's default container for 3D data.
 Use a MeshLoader to fill in the vertex and index information, and
 generate VBO lists.
 */
class VBOModel: public Model
{
public:
	VBOModel() :
		start_(0), end_(0), count_(0), ranks_(1), myrank_(0), isize(0),
				vsize(0), vbo_loaded(false), startindex((char *) NULL)
	{
	}

	//! Clear the model's index and vertex vector
	void clear();

	//! Check whether the model contains data
	/*!
	 \return True if index vector is empty, false if not
	 */
	bool empty() const;

	//! The vertex vector getter
	/*!
	 \return A const reference to the model's vertex vector
	 */
	std::vector<Vertex> const& get_vertices() const
	{
		return vertices;
	}

	//! The index vector getter
	/*!
	 \return A const reference to the model's index vector
	 */
	std::vector<std::size_t> const& get_indices() const
	{
		return indices;
	}

	//! Draw the model using vbo lists
	virtual void draw() const;

	//! Attempt to preallocate enough memory for specified number of vertices
	void reserve_vertices(std::size_t number);

	//! Attempt to preallocate enough memory for specified number of triangles
	void reserve_triangles(std::size_t number);

	//! Add a vertex to the vertex vector
	/*!
	 \param vertex A vertex const reference
	 */
	void add_vertex(Vertex const& vertex);

	//! Add a triangle to the index vector
	/*!
	 \param a The first vertex number of the triangle
	 \param b The second vertex number of the triangle
	 \param c The third vertex number of the triangle
	 */
	void add_triangle(std::size_t a, std::size_t b, std::size_t c);

	//! Returns the number of ranks processing a VBOModel in parallel
	/*!
	 \return The number of ranks in parallel rendering
	 */
	unsigned int getRanks() const
	{
		return ranks_;
	}

	//! Returns the rank's ID
	/*!
	 \return The node's rank ID
	 */
	unsigned int getMyRank() const
	{
		return myrank_;
	}

	/*! Metamethod to fix scale, normalize normals, generate VBO lists and
	 * set drawing range in the correct order
	 */
	/*!
	 \param myrank The rank ID of the Maoni instance
	 \param ranks The number of ranks processing a VBOModel in parallel
	 */
	void initVBO(unsigned int myrank, unsigned int ranks);

private:
	//! Scales the data to be within +- baseSize/2 (default 2.0) coordinates
	void fix_scale();

	//! Calculate and normalize the vertex normals of the current vertex data
	void calculate_normals();

	//! Creates VBO lists of the vertex data and indices
	void generate_vbo();

	//! Calculates and sets vertices to be drawn by a rendering node
	void setDrawRange(unsigned int myrank, unsigned int ranks);

	void setStartVertex(unsigned int start);
	void setEndVertex(unsigned int end);

private:
	std::vector<Vertex> vertices;
	std::vector<std::size_t> indices;

	bool vbo_loaded;
	unsigned int isize, vsize;
	unsigned int start_, end_, count_;
	unsigned int myrank_, ranks_;
	char* startindex;
};

#endif /* MAONI_VBO_MODEL_HPP */
