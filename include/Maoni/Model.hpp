/*
 * Model.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include "Vertex.hpp"
#include <vector>
#include <boost/array.hpp>

class Model
{
public:
	//! clear the model
	void clear();

	//!
	bool empty() const;

	//! draw the model
	void draw() const;

	void reserve_vertices(std::size_t number);

	void reserve_triangles(std::size_t number);

	void add_vertex(Vertex const& vertex);

	void add_triangle(std::size_t a, std::size_t b, std::size_t c);

	void fix_scale();

	//! Calculate the face or vertex normals of the current vertex data.
	void calculate_normals();

private:
	void calculateBoundingBox();

private:
	std::vector<Vertex> vertices;
	std::vector<std::size_t> indices;

	typedef boost::array<Vector3, 2> BoundingBox;
	BoundingBox bounding_box;
};

#endif /* MODEL_HPP */
