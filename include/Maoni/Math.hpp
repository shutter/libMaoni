/*
 * Math.hpp
 *
 *  Created on: 11.03.2010
 *      Author: daniel
 */

#ifndef MATH_HPP_
#define MATH_HPP_

#include <Maoni/Vector.hpp>
#include <cmath>

inline Vector3 operator+(Vector3 const& v1, Vector3 const& v2)
{
	return Vector3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline Vector3 operator-(Vector3 const& v1, Vector3 const& v2)
{
	return Vector3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline Vector3 operator*(Vector3 const& v, float s)
{
	return Vector3(v.x() * s, v.y() * s, v.z() * s);
}

inline Vector3 operator/(Vector3 const& v, float s)
{
	return Vector3(v.x() / s, v.y() / s, v.z() / s);
}

inline float length(Vector3 const& v)
{
	return std::sqrt(v.x() * v.x() + v.y() * v.y() + v.z() * v.z());
}

inline Vector3 normalize(Vector3 const& v)
{
	return v / length(v);
}

#endif /* MATH_HPP_ */
