/*
 * scoped_locks.hpp
 *
 *  Created on: 01.11.2009
 *      Author: Daniel Pfeifer
 */

#ifndef VMMVIEW_SCOPED_LOCKS_HPP
#define VMMVIEW_SCOPED_LOCKS_HPP

#include <Maoni/detail/ScopedLocks.hpp>

struct ScopedEnable: detail::ScopedEnable
{
	ScopedEnable(GLenum cap) :
		detail::ScopedEnable(cap)
	{
		glEnable(cap);
	}
};

struct ScopedDisable: detail::ScopedEnable
{
	ScopedDisable(GLenum cap) :
		detail::ScopedEnable(cap)
	{
		glDisable(cap);
	}
};

class ScopedUseProgram
{
public:
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

class ScopedBindTexture
{
public:
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
