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

// enumeration for the sort axis
enum Axis
{
	AXIS_X, AXIS_Y, AXIS_Z
};

typedef boost::array<Vector3, 2> BoundingBox;

class Model
{
public:
	Model();

	void sort(std::size_t start, std::size_t length, Axis axis);
	void scale(float baseSize = 2.0f);
	void calculateNormals();
	void calculateBoundingBox();
	const BoundingBox& getBoundingBox() const
	{
		return _boundingBox;
	}
	Axis getLongestAxis(std::size_t start, std::size_t elements) const;

	float getBoundingSphereRadius() const
	{
		return _radius;
	}

	typedef vmml::vector<3, std::size_t> Triangle;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

private:
	void calcBoundingSphereRadius();

	BoundingBox _boundingBox;
	float _radius;
};

#endif /* MODEL_HPP */
