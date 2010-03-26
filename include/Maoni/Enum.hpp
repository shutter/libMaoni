/*
 * enum.hpp
 *
 *  Created on: 02.11.2009
 *      Author: Daniel Pfeifer
 */

#ifndef MAONI_ENUM_HPP
#define MAONI_ENUM_HPP

#define ENUM(NAME, VALUES)                                                     \
	enum NAME { BOOST_PP_SEQ_ENUM(VALUES) };                                   \
	template<> const std::size_t enum_names<NAME>::size =                      \
			BOOST_PP_SEQ_SIZE(VALUES);                                         \
	template<> const char* const EnumNames<NAME>::stack[] = {                  \
			BOOST_PP_SEQ_FOR_EACH(COMMA_SEP_STRINGS,, VALUES) 0                \
	}                                                                          \

#include <Maoni/detail/Enum.hpp>

#endif /* MAONI_ENUM_HPP */
