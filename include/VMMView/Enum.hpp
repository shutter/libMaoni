/*
 * enum.hpp
 *
 *  Created on: 02.11.2009
 *      Author: Daniel Pfeifer
 */

#ifndef VMMVIEW_ENUM_HPP
#define VMMVIEW_ENUM_HPP

#define ENUM(NAME, VALUES)                                                     \
	enum NAME { BOOST_PP_SEQ_ENUM(VALUES) };                                   \
	template<> const std::size_t enum_names<NAME>::size =                      \
			BOOST_PP_SEQ_SIZE(VALUES);                                         \
	template<> const char* const EnumNames<NAME>::stack[] = {                  \
			BOOST_PP_SEQ_FOR_EACH(COMMA_SEP_STRINGS,, VALUES) 0                \
	}                                                                          \

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

#endif /* VMMVIEW_ENUM_HPP */
