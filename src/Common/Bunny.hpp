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

#ifndef MAONI_BUNNY_HPP
#define MAONI_BUNNY_HPP

#include <Maoni/Model.hpp>
#include <boost/scoped_array.hpp>
#include <vector>
#include <Maoni/Vertex.hpp>

class Bunny: public Model
{
public:
	//! Creating a model object from scratch initialized by the Stanford Bunny
	Bunny();

	//! Draw the bunny
	virtual void draw() const;

private:
	void calculate_normals();
	void fix_scale();

private:
	size_t indices;
	size_t vertices;
	std::vector<Vertex> verticesv;
	std::vector<std::size_t> indicesv;
};
#endif /* MAONI_BUNNY_HPP */

