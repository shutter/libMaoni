/*
 * Vertex.hpp
 *
 *  Created on: Jul 30, 2009
 *      Author: dpfeifer
 */

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Vector.hpp"
#include "Color.hpp"

struct Vertex
{
	Vertex(float x, float y, float z) :
		position(x, y, z)
	{
	}

	Vertex(
			const Vec3& position_,
			const Vec3& normal_,
			const Color& color_,
			const Vec2& texcoord_) :
		position(position_), normal(normal_), color(color_),
				texcoord(texcoord_)
	{
	}

	Vertex(const Vertex& other) :
		position(other.position), normal(other.normal), color(other.color),
				texcoord(other.texcoord)
	{
	}

	const Vertex& operator=(const Vertex& other)
	{
		position = other.position;
		normal = other.normal;
		color = other.color;
		texcoord = other.texcoord;
		return *this;
	}

	Vec3 position;
	Vec3 normal;
	Color color;
	Vec2 texcoord;
};

#endif /* VERTEX_HPP */
