/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
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

#ifndef VMMVIEW_SHADER_PROGRAM_HPP
#define VMMVIEW_SHADER_PROGRAM_HPP

/**
 * \brief Define shader source code.
 *
 * Expands shader name, GLSL version directives and the source code to a
 * shader source stored as const char array
 */
#define SHADER_SOURCE(NAME, DIRECTIVES, SOURCE) const char* const NAME =       \
	BOOST_PP_SEQ_FOLD_LEFT(SHADER_FOLD_DIRECTIVES,, DIRECTIVES) #SOURCE        \

/**
 * \brief Define a shader program.
 *
 * Expands program name, shader sources and uniform buffer objects to a
 * shader program struct
 */
#define SHADER_PROGRAM(NAME, SOURCE, UNIFORM)                                  \
	SHADER_PROGRAM_I(NAME,                                                     \
		BOOST_PP_CAT(SHADER_PROGRAM_SOURCE_X SOURCE, 0),                       \
		BOOST_PP_CAT(SHADER_PROGRAM_UNIFORM_X UNIFORM, 0))                     \

#include <Maoni/detail/ShaderProgram.hpp>

#endif /* VMMVIEW_SHADER_PROGRAM_HPP */
