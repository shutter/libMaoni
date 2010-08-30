/*
 * libMaoni - common viewing framework
 *
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 * Visualization and Multimedia Lab, University of Zurich
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

#ifndef MAONI_DETAIL_VECTOR_HPP
#define MAONI_DETAIL_VECTOR_HPP

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>

namespace detail
{

template<int D>
struct VectorBase
{
	operator const float*() const
	{
		return data;
	}

	float data[D];
};

template<int D>
struct Vector: VectorBase<D>
{
};

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

} // namespace detail

namespace boost
{
namespace la
{

template<class Vector>
struct vector_traits;

template<int D>
struct vector_traits< ::detail::Vector<D> >
{
	typedef ::detail::Vector<D> vector_type;
	typedef float scalar_type;
	static const int dim = D;

	template<int I>
	static scalar_type r(vector_type const& vector)
	{
		BOOST_STATIC_ASSERT(I >= 0);
		BOOST_STATIC_ASSERT(I < dim);
		return vector.data[I];
	}

	template<int I>
	static scalar_type & w(vector_type & vector)
	{
		BOOST_STATIC_ASSERT(I >= 0);
		BOOST_STATIC_ASSERT(I < dim);
		return vector.data[I];
	}

	static scalar_type ir(int i, vector_type const& vector)
	{
		BOOST_ASSERT(i >= 0);
		BOOST_ASSERT(i < dim);
		return vector.data[i];
	}

	static scalar_type & iw(int i, vector_type & vector)
	{
		BOOST_ASSERT(i >= 0);
		BOOST_ASSERT(i < dim);
		return vector.data[i];
	}
};

} // namespace la
} // namespace boost

#endif /* MAONI_DETAIL_VECTOR_HPP */
