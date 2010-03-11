/*
 * Vector.hpp
 *
 *  Created on: 27.07.2009
 *      Author: daniel
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vmmlib/vector.hpp>

//! a two component floating-point vector
class Vector2
{
public:
	Vector2()
	{
		impl[0] = impl[1] = 0.f;
	}

	Vector2(float x, float y)
	{
		impl[0] = x;
		impl[1] = y;
	}

	Vector2(Vector2 const& other)
	{
		impl[0] = other.x();
		impl[1] = other.y();
	}

	float x() const
	{
		return impl[0];
	}

	float y() const
	{
		return impl[1];
	}

	operator const float*() const
	{
		return impl;
	}

private:
	float impl[2];
};

//! a three component floating-point vector
typedef vmml::vector<3, float> Vector3;

//! a four component floating-point vector
typedef vmml::vector<4, float> Vector4;

#endif /* VECTOR_HPP */
