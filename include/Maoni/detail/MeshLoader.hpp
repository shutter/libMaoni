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
        void load(Model::Ptr& model, const char* filename) const;              \
                                                                               \
        static LOADER instance;                                                \
    };                                                                         \
                                                                               \
    LOADER LOADER::instance;                                                   \
    void LOADER::load(Model::Ptr& model, const char* filename) const           \

#endif /* MAONI_DETAIL_MESH_LOADER_HPP */
