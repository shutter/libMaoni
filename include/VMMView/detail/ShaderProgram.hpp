/*
 * shader_program.hpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_COMMON_SHADER_PROGRAM_HPP
#define VMMVIEW_COMMON_SHADER_PROGRAM_HPP

#include <GL/gl.h>
#include <set>
#include <iostream>

class ShaderProgram
{
public:
	ShaderProgram() :
		name(0)
	{
	}

	ShaderProgram(ShaderProgram const& other) :
		name(0), shaders(other.shaders)
	{
	}

	~ShaderProgram()
	{
		if (name)
			glDeleteProgram(name);
	}

	const ShaderProgram& operator=(ShaderProgram const& other)
	{
		if (name)
		{
			glDeleteProgram(name);
			name = 0;
		}

		shaders = other.shaders;
		return *this;
	}

	operator GLuint() const;

protected:
	void attach(GLenum type, const GLchar* source)
	{
		shaders.insert(shader_t(type, source));
	}

private:
	mutable GLuint name;

	typedef std::pair<GLenum, const GLchar*> shader_t;
	typedef std::set<shader_t> shader_set_t;
	shader_set_t shaders;
};

#endif /* VMMVIEW_COMMON_SHADER_PROGRAM_HPP */
