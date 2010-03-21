/*
 * shader_program.hpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_SHADER_PROGRAM_HPP
#define VMMVIEW_SHADER_PROGRAM_HPP

/**
 * \brief Define shader source code.
 *
 * bla blubb
 */
#define SHADER_SOURCE(NAME, DIRECTIVES, SOURCE) const char* const NAME =       \
	BOOST_PP_SEQ_FOLD_LEFT(SHADER_FOLD_DIRECTIVES,, DIRECTIVES) #SOURCE        \

/**
 * \brief Define a shader program.
 *
 * bla blubb
 */
#define SHADER_PROGRAM(NAME, SOURCE, UNIFORM)                                  \
	SHADER_PROGRAM_I(NAME,                                                     \
		BOOST_PP_CAT(SHADER_PROGRAM_SOURCE_X SOURCE, 0),                       \
		BOOST_PP_CAT(SHADER_PROGRAM_UNIFORM_X UNIFORM, 0))                     \

#include <Maoni/detail/ShaderProgram.hpp>

#endif /* VMMVIEW_SHADER_PROGRAM_HPP */
