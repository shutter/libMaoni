/*
 * VMMView.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#ifndef MAONI_RENDER_ALGORITHM_HPP
#define MAONI_RENDER_ALGORITHM_HPP

#include <Maoni/detail/Extensible.hpp>

class Enum;
class Path;
class Color;
class Model;
class ShaderProgram;

struct AlgorithmConfig
{
	virtual void property(const char* name, int& value) = 0;
	virtual void property(const char* name, bool& value) = 0;
	virtual void property(const char* name, float& value) = 0;
	virtual void property(const char* name, double& value) = 0;
	virtual void property(const char* name, Enum& value) = 0;
	virtual void property(const char* name, Path& value) = 0;
	virtual void property(const char* name, Color& value) = 0;
	virtual void property(const char* name, ShaderProgram& value) = 0;
};

struct RenderAlgorithm: Extensible<RenderAlgorithm>
{
	virtual const char* name() const = 0;

	virtual void render(const Model& model) const = 0;

	virtual void config(AlgorithmConfig& algo_config) = 0;
};

/**
 * Define a custom render algorithm.
 *
 * Some description on how to use this macro.
 *
 * \param NAME The name of this algorithm.
 * \param BSEQ A sequence of parameters. Each parameter has the form
 * (type, value, default)
 */
#define RENDER_ALGORITHM(NAME, BSEQ) \
    RENDER_ALGORITHM_I(NAME, BOOST_PP_CAT(RENDER_ALGORITHM_X BSEQ, 0))

#include <Maoni/detail/Algorithm_PP.hpp>

#endif /* MAONI_RENDER_ALGORITHM_HPP */
