/*
 * shader_program.hpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
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
