/*
 * shader_program.hpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_SHADER_PROGRAM_HPP
#define VMMVIEW_SHADER_PROGRAM_HPP

#define SHADER_SOURCE(NAME, SOURCE)                                            \
	const char* const NAME = "#version 130\n" #SOURCE                          \

#define SHADER_PROGRAM(NAME, SOURCE, UNIFORM)                                  \
	SHADER_PROGRAM_I(NAME,                                                     \
		BOOST_PP_CAT(SHADER_PROGRAM_SOURCE_X SOURCE, 0),                       \
		BOOST_PP_CAT(SHADER_PROGRAM_UNIFORM_X UNIFORM, 0))                     \

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <VMMView/detail/ShaderProgram.hpp>

#define SHADER_PROGRAM_SOURCE_X(TYPE, C_STR) \
	((GL_##TYPE##_SHADER, C_STR)) SHADER_PROGRAM_SOURCE_Y

#define SHADER_PROGRAM_SOURCE_Y(TYPE, C_STR) \
	((GL_##TYPE##_SHADER, C_STR)) SHADER_PROGRAM_SOURCE_X

#define SHADER_PROGRAM_SOURCE_X0
#define SHADER_PROGRAM_SOURCE_Y0

#define SHADER_PROGRAM_UNIFORM_X(X, Y, Z) ((X, Y, Z)) SHADER_PROGRAM_UNIFORM_Y
#define SHADER_PROGRAM_UNIFORM_Y(X, Y, Z) ((X, Y, Z)) SHADER_PROGRAM_UNIFORM_X
#define SHADER_PROGRAM_UNIFORM_X0
#define SHADER_PROGRAM_UNIFORM_Y0

#define SHADER_PROGRAM_I(NAME, SOURCE, UNIFORM_NOT_USED_YET)                   \
	struct NAME: ShaderProgram                                                 \
	{                                                                          \
		NAME() { BOOST_PP_SEQ_FOR_EACH(SHADER_PROGRAM_ATTACH,, SOURCE) }       \
	}                                                                          \

#define SHADER_PROGRAM_ATTACH(R, DATA, ELEM)                                   \
   ShaderProgram::attach(BOOST_PP_TUPLE_ELEM(2, 0, ELEM),                      \
                         BOOST_PP_TUPLE_ELEM(2, 1, ELEM));                     \

#endif /* VMMVIEW_SHADER_PROGRAM_HPP */
