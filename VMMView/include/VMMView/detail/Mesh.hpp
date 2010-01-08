/*
 * Mesh.hpp
 *
 *  Created on: Jul 30, 2009
 *      Author: shutter
 */

#ifndef MESH_HPP
#define MESH_HPP

#include "Vertex.hpp"
#include <vector>
#include <boost/array.hpp>

// enumeration for the sort axis
enum Axis
{
	AXIS_X, AXIS_Y, AXIS_Z
};

typedef boost::array<Vector3, 2> BoundingBox;

class Mesh
{
public:
	Mesh();

	void sort(std::size_t start, std::size_t length, Axis axis);
	void scale(float baseSize = 2.0f);
	void calculateNormals();
	void calculateBoundingBox();
	const BoundingBox& getBoundingBox() const
	{
		return _boundingBox;
	}
	Axis getLongestAxis(std::size_t start, std::size_t elements) const;

	//	void useInvertedFaces() {
	//		_invertFaces = true;
	//	}

	float getBoundingSphereRadius() const
	{
		return _radius;
	}

	typedef vmml::vector<3, std::size_t> Triangle;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

private:
	//	void readVertices(PlyFile* file, int nVertices);
	//	void readTriangles(PlyFile* file, int nFaces);

	void calcBoundingSphereRadius();

	BoundingBox _boundingBox;
	float _radius;
	//	bool _invertFaces;
};

#endif /* MESH_HPP */
