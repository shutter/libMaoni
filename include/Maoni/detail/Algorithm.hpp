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
