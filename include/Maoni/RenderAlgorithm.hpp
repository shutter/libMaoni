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

#ifndef MAONI_RENDER_ALGORITHM_HPP
#define MAONI_RENDER_ALGORITHM_HPP

#include <Maoni/detail/Extensible.hpp>
#include <Maoni/Model.hpp>

class Enum;
class Path;
class Color;
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
 * \brief Define a custom render algorithm.
 *
 * Extends the algorithm name and its GUI controlled variables to a
 * RenderAlgorithm subclass, which will be linked against libMaoni.
 * The macro ensures the right interface to make the algorithm available
 * in the drop down menu of the render algorithm widget.
 * Have a look at the RenderAlgorithm-tutorial and algorithm examples for
 * information about concrete implementation.
 *
 * \param NAME The name of this algorithm.
 * \param BSEQ A sequence of parameters. Each parameter has the form
 * (type, value, default)
 */
#define RENDER_ALGORITHM(NAME, BSEQ) \
    RENDER_ALGORITHM_I(NAME, BOOST_PP_CAT(RENDER_ALGORITHM_X BSEQ, 0))

#include <Maoni/detail/Algorithm_PP.hpp>

#endif /* MAONI_RENDER_ALGORITHM_HPP */
