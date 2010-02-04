/*
 * shader_program.hpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_COMMON_SHADER_PROGRAM_HPP
#define VMMVIEW_COMMON_SHADER_PROGRAM_HPP

#include <set>

class ShaderProgram
{
public:
	ShaderProgram();

	ShaderProgram(ShaderProgram const& other);

	~ShaderProgram();

	const ShaderProgram& operator=(ShaderProgram const& other);

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
