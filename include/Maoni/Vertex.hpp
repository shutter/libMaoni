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

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Vector.hpp"
#include "Color.hpp"

//! A vertex struct
/*!
  The vertex container can hold information about position, vertex normal, color and
  texture coordinates of a single vertex.
*/

struct Vertex
{
	//! Create a vertex having only its position set implicit.
    /*!
      \param x The x-coordinate of the vertex position
      \param y The y-coordinate of the vertex position
      \param z The z-coordinate of the vertex position
    */
	Vertex(float x, float y, float z) :
		position(x, y, z)
	{
	}

	//! Create a vertex having its complete information set.
    /*!
      \param position_ A const reference to the vertex position vector
      \param normal_ A const reference to the vertex normal vector
      \param color_ A const reference to the vertex color vector
	  \param texcoord_ A const reference to the vertex texture coordinate vector
    */
	Vertex(
			const Vec3& position_,
			const Vec3& normal_,
			const Color& color_,
			const Vec2& texcoord_) :
		position(position_), normal(normal_), color(color_),
				texcoord(texcoord_)
	{
	}

	//! Create a vertex by using the data of another one.
	/*!
	  \param other A const reference to a vertex
	 */
	Vertex(const Vertex& other) :
		position(other.position), normal(other.normal), color(other.color),
				texcoord(other.texcoord)
	{
	}

	//! Overwrite the vertex data by the data of another vertex when using the assignment operator
	/*!
	  \param other A const reference to a vertex
	 */
	const Vertex& operator=(const Vertex& other)
	{
		position = other.position;
		normal = other.normal;
		color = other.color;
		texcoord = other.texcoord;
		return *this;
	}

	//! The vertex' position vector
	Vec3 position;

	//! The vertex' normal vector
	Vec3 normal;

	//! The vertex' color information
	Color color;

	//! The vertex' texture coordinates
	Vec2 texcoord;
};

#endif /* VERTEX_HPP */
