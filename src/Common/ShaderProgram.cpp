/*
 * shader_program.cpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
 */

#include <VMMView/detail/ShaderProgram.hpp>
#include <iostream>

ShaderProgram::ShaderProgram() :
	name(0)
{
}

ShaderProgram::ShaderProgram(ShaderProgram const& other) :
	name(0), shaders(other.shaders)
{
}

ShaderProgram::~ShaderProgram()
{
	if (name)
		glDeleteProgram(name);
}

const ShaderProgram& ShaderProgram::operator=(ShaderProgram const& other)
{
	if (name)
	{
		glDeleteProgram(name);
		name = 0;
	}

	shaders = other.shaders;
	return *this;
}

ShaderProgram::operator GLuint() const
{
	if (!name)
	{
		GLint success;
		GLint length;

		name = glCreateProgram();

		typedef shader_set_t::const_iterator iter;
		for (iter i = shaders.begin(); i != shaders.end(); ++i)
		{
			GLenum type = i->first;
			const GLchar* source = i->second;

			GLuint shader = glCreateShader(type);
			glShaderSource(shader, 1, &source, 0);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			if (length > 0)
			{
				std::string log(length, 0);
				glGetShaderInfoLog(shader, length, 0, &log[0]);
				std::clog << log << std::endl;
			}

			if (!success)
			{
				std::cerr << "error compiling shader" << std::endl;
				return 0;
			}

			glAttachShader(name, shader);
			glDeleteShader(shader);
		}

		glLinkProgram(name);

		glGetProgramiv(name, GL_LINK_STATUS, &success);
		if (!success)
			std::cerr << "error linking program" << std::endl;

		glGetProgramiv(name, GL_INFO_LOG_LENGTH, &length);
		if (length > 0)
		{
			std::string log(length, 0);
			glGetProgramInfoLog(name, length, 0, &log[0]);
			std::clog << log << std::endl;
		}
	}

	return name;
}
