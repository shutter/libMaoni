/*
 * Mesh.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: shutter
 */

#include <VMMView/Model.hpp>
#include <cstdlib>
#include <algorithm>

Model::Model() : /*_invertFaces( false ),*/
	_radius(0.0)
{
	_boundingBox[0] = Vector3(0.0f);
	_boundingBox[1] = Vector3(0.0f);
}

/*  Calculate the face or vertex normals of the current vertex data.  */
void Model::calculateNormals()
{
	// iterate over all triangles and add their normals to adjacent vertices
	Vector3 triangleNormal;
	std::size_t i0, i1, i2;
	for (size_t i = 0; i < triangles.size(); ++i)
	{
		i0 = triangles[i].at(0);
		i1 = triangles[i].at(1);
		i2 = triangles[i].at(2);
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

/*  Calculate the bounding box of the current vertex data.  */
void Model::calculateBoundingBox()
{
	_boundingBox[0] = vertices[0].position.array;
	_boundingBox[1] = vertices[0].position.array;
	for (size_t v = 1; v < vertices.size(); ++v)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			_boundingBox[0][i] = std::min(_boundingBox[0][i],
					vertices[v].position[i]);
			_boundingBox[1][i] = std::max(_boundingBox[1][i],
					vertices[v].position[i]);
		}
	}
}

/* Calculates longest axis for a set of triangles */
Axis Model::getLongestAxis(const size_t start, const size_t elements) const
{
	if (start + elements > triangles.size())
	{
		std::cerr << "incorrect request to getLongestAxis" << std::endl
				<< "start:     " << start << std::endl << "elements:  "
				<< elements << std::endl << "sum:       " << start + elements
				<< std::endl << "data size: " << triangles.size() << std::endl;
		return AXIS_X;
	}

	BoundingBox bb;
	bb[0] = vertices[triangles[start][0]].position;
	bb[1] = vertices[triangles[start][0]].position;

	for (size_t t = start; t < start + elements; ++t)
	{
		for (size_t v = 0; v < 3; ++v)
		{
			for (size_t i = 0; i < 3; ++i)
			{
				bb[0][i] = std::min(bb[0][i],
						vertices[triangles[t][v]].position[i]);
				bb[1][i] = std::max(bb[1][i],
						vertices[triangles[t][v]].position[i]);
			}
		}
	}

	const float bbX = bb[1][0] - bb[0][0];
	const float bbY = bb[1][1] - bb[0][1];
	const float bbZ = bb[1][2] - bb[0][2];

	if (bbX >= bbY && bbX >= bbZ)
		return AXIS_X;

	if (bbY >= bbX && bbY >= bbZ)
		return AXIS_Y;

	return AXIS_Z;
}

/* calculate the bounding sphere radius from the bounding box */
void Model::calcBoundingSphereRadius()
{
	// calculate bounding box if not yet done
	if (_boundingBox[0].length() == 0.0f && _boundingBox[1].length() == 0.0f)
		calculateBoundingBox();

	float neg_rad = sqrt(pow(_boundingBox[0][0], 2)
			+ pow(_boundingBox[0][1], 2) + pow(_boundingBox[0][2], 2));

	float pos_rad = sqrt(pow(_boundingBox[1][0], 2)
			+ pow(_boundingBox[1][1], 2) + pow(_boundingBox[1][2], 2));

	_radius = std::max(neg_rad, pos_rad);
}

/*  Scales the data to be within +- baseSize/2 (default 2.0) coordinates.  */
void Model::scale(const float baseSize)
{
	// calculate bounding box if not yet done
	calculateBoundingBox();

	// find largest dimension and determine scale factor
	float factor = 0.0f;
	for (size_t i = 0; i < 3; ++i)
		factor = std::max(factor, _boundingBox[1][i] - _boundingBox[0][i]);

	factor = baseSize / factor;

	// determine scale offset
	Vector3 offset;
	for (size_t i = 0; i < 3; ++i)
		offset[i] = (_boundingBox[0][i] + _boundingBox[1][i]) * 0.5f;

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
			_boundingBox[v][i] -= offset[i];
			_boundingBox[v][i] *= factor;
		}
	}

	// calc the bounding sphere radius
	calcBoundingSphereRadius();
}
