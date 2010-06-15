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

#ifndef VMMVIEW_COMMON_SHADER_PROGRAM_HPP
#define VMMVIEW_COMMON_SHADER_PROGRAM_HPP

#include <set>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

#define SHADER_FOLD_DIRECTIVES(s, state, x) state "#" BOOST_PP_STRINGIZE(x) "\n"

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


//! ShaderProgramm Class
/*!
  To be able to use shaders in a RenderAlgorithm, they have to be compiled.
  This class holds the shader sources and compiles them to a shader program
  as soon as it is accessed.
*/
class ShaderProgram
{
public:
	//! Constructs an empty shader program
	ShaderProgram();

	//! Constructs a shader program by copying the shader sources of another program
	ShaderProgram(ShaderProgram const& other);

	//! Destruct the shader program and removes it from the OpenGL state machine
	~ShaderProgram();

	const ShaderProgram& operator=(ShaderProgram const& other);

	//! Compiles the shaders to a shader program
	/*!
	  \return The OpenGL handle of this shader program
	 */
	operator unsigned int() const;

protected:
	void attach(unsigned int type, const char* source)
	{
		shaders.insert(shader_t(type, source));
	}

private:
	mutable unsigned int name;

	typedef std::pair<unsigned int, const char*> shader_t;
	typedef std::set<shader_t> shader_set_t;
	shader_set_t shaders;
};

#endif /* VMMVIEW_COMMON_SHADER_PROGRAM_HPP */
