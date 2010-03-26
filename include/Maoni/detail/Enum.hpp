/*
 * enum.hpp
 *
 *  Created on: 02.11.2009
 *      Author: Daniel Pfeifer
 */

#ifndef MAONI_DETAIL_ENUM_HPP
#define MAONI_DETAIL_ENUM_HPP

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_enum.hpp>

#define COMMA_SEP_STRINGS(r, data, elem) BOOST_PP_STRINGIZE(elem),             \

template<typename T>
struct EnumNames
{
	static const std::size_t size;
	static const char* const stack[];
};

#endif /* MAONI_DETAIL_ENUM_HPP */
