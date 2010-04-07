/*
 * Vector.hpp
 *
 *  Created on: 27.07.2009
 *      Author: daniel
 */

#ifndef MAONI_VECTOR_HPP
#define MAONI_VECTOR_HPP

#include <Maoni/detail/Vector.hpp>

//! a two component floating-point vector
typedef Vector<2> Vector2;

template<>
struct Vector<2> : VectorBase<2>
{
	Vector()
	{
		data[0] = data[1] = 0.f;
	}

	Vector(float x, float y)
	{
		data[0] = x;
		data[1] = y;
	}
};

//! a three component floating-point vector
typedef Vector<3> Vector3;

template<>
struct Vector<3> : VectorBase<3>
{
	Vector()
	{
		data[0] = data[1] = data[2] = 0.f;
	}

	Vector(float x, float y, float z)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}
};

//! a four component floating-point vector
typedef Vector<4> Vector4;

template<>
struct Vector<4> : VectorBase<4>
{
	Vector()
	{
		data[0] = data[1] = data[2] = data[3] = 0.f;
	}

	Vector(float x, float y, float z, float w)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}
};

#endif /* MAONI_VECTOR_HPP */
