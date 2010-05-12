/*
 * RenderAlgorithm.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#ifndef VMMVIEW_COMMON_RENDER_ALGORITHM_HPP
#define VMMVIEW_COMMON_RENDER_ALGORITHM_HPP

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

struct Algorithm: Extensible<Algorithm>
{
	virtual const char* name() const = 0;

	virtual void render(const Model& model) const = 0;

	virtual void config(AlgorithmConfig& algo_config) = 0;
};

#endif /* VMMVIEW_COMMON_RENDER_ALGORITHM_HPP */
