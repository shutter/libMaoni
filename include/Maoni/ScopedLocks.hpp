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

#ifndef VMMVIEW_SCOPED_LOCKS_HPP
#define VMMVIEW_SCOPED_LOCKS_HPP

#include <Maoni/detail/ScopedLocks.hpp>

/*!
  Enable an OpenGL setting by creating an ScopedEnable object to ensure it is
  reset to its original state when the RenderAlgorithm is switched (RAII)
 */
struct ScopedEnable: detail::ScopedEnable
{
	//! Constructs a ScopedEnable object and enables a certain OpenGL state parameter
    /*!
      \param cap An OpenGL state parameter's number
    */
	ScopedEnable(GLenum cap) :
		detail::ScopedEnable(cap)
	{
		glEnable(cap);
	}
};

/*!
  Disable an OpenGL setting by creating an ScopedDisable object to ensure it is
  reset to its original state when the RenderAlgorithm is switched (RAII)
 */
struct ScopedDisable: detail::ScopedEnable
{
	//! Constructs a ScopedDisable object and disable a certain OpenGL state parameter
    /*!
      \param cap An OpenGL state parameter's number
    */
	ScopedDisable(GLenum cap) :
		detail::ScopedEnable(cap)
	{
		glDisable(cap);
	}
};

/*!
  Loads a shader program and ensures that it is removed from the OpenGL state machine
  when the RenderAlgorithm is switched (RAII)
 */
class ScopedUseProgram
{
public:
	//! Constructs a ScopedUseProgram object and loads the shader program
    /*!
      \param name The shader handle of the RenderAlgorithm
    */
	ScopedUseProgram(GLint name)
	{
		glGetIntegerv(GL_CURRENT_PROGRAM, &name_);
		glUseProgram(name);
	}

	~ScopedUseProgram()
	{
		glUseProgram(name_);
	}

private:
	GLint name_;
};

/*!
  Binds a texture and ensures that it is removed from the OpenGL state machine
  when the RenderAlgorithm is switched (RAII)
 */
class ScopedBindTexture
{
public:
	//! Constructs a ScopedBindTexture object and binds the texture
	/*!
	  \param name The OpenGL Texture handle
	 */
	ScopedBindTexture(GLint name)
	{
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &name_);
		glBindTexture(GL_TEXTURE_2D, name);
	}

	~ScopedBindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, name_);
	}

private:
	GLint name_;
};

#endif /* VMMVIEW_SCOPED_LOCKS_HPP */
