/*
 * Vector.hpp
 *
 *  Created on: 27.07.2009
 *      Author: daniel
 */

#ifndef MAONI_VECTOR_HPP
#define MAONI_VECTOR_HPP

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
class Vector3
{
public:
	Vector3()
	{
		impl[0] = impl[1] = impl[2] = 0.f;
	}

	Vector3(float x, float y, float z)
	{
		impl[0] = x;
		impl[1] = y;
		impl[2] = z;
	}

	Vector3(Vector3 const& other)
	{
		impl[0] = other.x();
		impl[1] = other.y();
		impl[2] = other.z();
	}

	float x() const
	{
		return impl[0];
	}

	float y() const
	{
		return impl[1];
	}

	float z() const
	{
		return impl[2];
	}

	operator const float*() const
	{
		return impl;
	}

	// TODO remove this!
	operator float*()
	{
		return impl;
	}

private:
	float impl[3];
};

//! a four component floating-point vector
class Vector4
{
public:
	Vector4()
	{
		impl[0] = impl[1] = impl[2] = impl[3] = 0.f;
	}

	Vector4(float x, float y, float z, float w)
	{
		impl[0] = x;
		impl[1] = y;
		impl[2] = z;
		impl[3] = w;
	}

	Vector4(Vector4 const& other)
	{
		impl[0] = other.x();
		impl[1] = other.y();
		impl[2] = other.z();
		impl[3] = other.w();
	}

	float x() const
	{
		return impl[0];
	}

	float y() const
	{
		return impl[1];
	}

	float z() const
	{
		return impl[2];
	}

	float w() const
	{
		return impl[3];
	}

	operator const float*() const
	{
		return impl;
	}

private:
	float impl[4];
};

#endif /* MAONI_VECTOR_HPP */
