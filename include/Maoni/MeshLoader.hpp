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

#ifndef MAONI_MESH_LOADER_HPP
#define MAONI_MESH_LOADER_HPP

#include <Maoni/Model.hpp>
#include <Maoni/detail/Extensible.hpp>

struct MeshLoader: Extensible<MeshLoader>
{
	virtual const char* const name() const = 0;
	virtual const char* const extension() const = 0;
	virtual void load(Model& mesh, const char* filename) const = 0;
};

/**
 * Define a custom MeshLoader.
 *
 * Some description on how to use this macro.
 *
 * \param EXT  The file extension associated with this loader
 * \param NAME The name of the file format.
 */
#define MESH_LOADER(EXT, NAME) MESH_LOADER_I(MeshLoader_##EXT, #NAME, #EXT)

#include <Maoni/detail/MeshLoader.hpp>

#endif /* MAONI_MESH_LOADER_HPP */
