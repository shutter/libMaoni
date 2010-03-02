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

	void reserve_quads(std::size_t number);

	void add_vertex(Vertex const& vertex);

	void add_triangle(std::size_t a, std::size_t b, std::size_t c);

	void add_quad(std::size_t a, std::size_t b, std::size_t c, std::size_t d);

	void fix_scale();

	//! Calculate the face or vertex normals of the current vertex data.
	void calculate_normals();

private:
	void calculateBoundingBox();

private:
	typedef boost::array<std::size_t, 3> Triangle;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	typedef boost::array<Vector3, 2> BoundingBox;
	BoundingBox bounding_box;
};

#endif /* MODEL_HPP */
