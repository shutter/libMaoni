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

#ifndef MAONI_DETAIL_MESH_LOADER_HPP
#define MAONI_DETAIL_MESH_LOADER_HPP

#include <Maoni/Model.hpp>
#include <Maoni/detail/Extensible.hpp>

struct MeshLoader: Extensible<MeshLoader>
{
	virtual const char* const name() const = 0;
	virtual const char* const extension() const = 0;
	virtual bool load(Model& mesh, const char* filename) const = 0;
};

#define MESH_LOADER_I(LOADER, NAME, EXTENSION)                                 \
    class LOADER: public MeshLoader                                            \
    {                                                                          \
        const char* const name() const                                         \
        {                                                                      \
            return NAME;                                                       \
        }                                                                      \
                                                                               \
        const char* const extension() const                                    \
        {                                                                      \
            return EXTENSION;                                                  \
        }                                                                      \
                                                                               \
        bool load(Model& model, const char* filename) const;                   \
                                                                               \
        static LOADER instance;                                                \
    };                                                                         \
                                                                               \
    LOADER LOADER::instance;                                                   \
    bool LOADER::load(Model& model, const char* filename) const                \

#endif /* MAONI_DETAIL_MESH_LOADER_HPP */
