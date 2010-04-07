/*
 * Vector.hpp
 *
 *  Created on: 27.07.2009
 *      Author: daniel
 */

#ifndef MAONI_DETAIL_VECTOR_HPP
#define MAONI_DETAIL_VECTOR_HPP

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/la/vector_assign.hpp>

template<int D>
struct VectorBase
{
	operator const float*() const
	{
		return data;
	}

	template<class R>
	operator R() const
	{
		R r;
		boost::la::assign(r, *this);
		return r;
	}

	float data[D];
};

template<int D>
struct Vector: VectorBase<D>
{
};

namespace boost
{
namespace la
{

template<class Vector>
struct vector_traits;

template<int D>
struct vector_traits<Vector<D> >
{
	typedef Vector<D> vector_type;
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
