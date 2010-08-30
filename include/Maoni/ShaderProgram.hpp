/*
 * libMaoni - common viewing framework
 *
 * Copyright (C) 2009, 2010 Daniel Pfeifer, Stefan Hutter
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

#ifndef MAONI_SHADER_PROGRAM_HPP
#define MAONI_SHADER_PROGRAM_HPP

#include <set>

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

	//! Overwrite the shader program by another one when using the assignment operator
	/*!
	  \param other A const reference to a shader program
	 */
	const ShaderProgram& operator=(ShaderProgram const& other);

	//! Compiles the shaders to a shader program
	/*!
	  \return The OpenGL handle of this shader program
	 */
	operator unsigned int() const;

protected:
	//! Add a shader to the list of shaders of a shader program
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
 * Expands program name, shader sources and uniform buffer (to be implemented)
 * objects to a shader program struct
 */
#define SHADER_PROGRAM(NAME, SOURCE, UNIFORM)                                  \
	SHADER_PROGRAM_I(NAME,                                                     \
		BOOST_PP_CAT(SHADER_PROGRAM_SOURCE_X SOURCE, 0),                       \
		BOOST_PP_CAT(SHADER_PROGRAM_UNIFORM_X UNIFORM, 0))                     \

#include <Maoni/detail/ShaderProgram.hpp>

#endif /* MAONI_SHADER_PROGRAM_HPP */
