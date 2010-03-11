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
#include <boost/noncopyable.hpp>

class Model: private boost::noncopyable
{
public:
	enum BezierMesh
	{
		none, teapot, teacup, teaspoon, spiral
	};

	Model() :
		bezier_mesh(teapot)
	{
	}

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

	bool set_bezier_mesh(BezierMesh mesh)
	{
		bezier_mesh = mesh;
		return true;
	}

private:
	void calculateBoundingBox();

private:
	std::vector<Vertex> vertices;
	std::vector<std::size_t> indices;

	typedef boost::array<Vector3, 2> BoundingBox;
	BoundingBox bounding_box;

	BezierMesh bezier_mesh;
};

#endif /* MODEL_HPP */
