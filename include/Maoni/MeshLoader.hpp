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

/**
 * \brief Base class MeshLoader
 *
 * Defines the public interface for any file loader using the MESH_LOADER
 * macro. The methods name() and extension() are created by the macro
 * automatically and are used by the load dialog in the main menu.
 * The load() method has to be implemented by yourself and defines what
 * has to be done when a file in the file open dialog has been chosen.
 *
 * MESH_LOADER(extension, name){load stub}
 */
struct MeshLoader: Extensible<MeshLoader>
{
	//! Signature of a method which returns a file loader's name
    /*!
      \return A const pointer to the file loader's name
    */
	virtual const char* const name() const = 0;

	//! Signature of a method which returns a file loader's file extension
    /*!
      \return A const pointer to the file loader's file extension
    */
	virtual const char* const extension() const = 0;

	//! Signature of the method which is called when a file has been chosen to be loaded
    /*!
      \param mesh A scoped pointer reference to the model
      \param filename A const char pointer to the file path and name
      \param rank The clients rank ID in parallel rendering
      \param max The number of clients in parallel rendering
    */
	virtual void load(Model::Ptr& mesh, const char* filename,
			int rank, int max) const = 0;
};

/**
 * \brief Define a custom MeshLoader.
 *
 * Extends a model file extension and description to a MeshLoader subclass,
 * which will be linked against libMaoni.
 * The macro ensures the right interface to make the new file type available
 * in the model-file choose dialog.
 * Have a look at the MeshLoader tutorial and loader examples for information
 * about concrete implementation.
 *
 * \param EXT  The file extension associated with this loader
 * \param NAME The name of the file format.
 */
#define MESH_LOADER(EXT, NAME) MESH_LOADER_I(MeshLoader_##EXT, #NAME, #EXT)

#include <Maoni/detail/MeshLoader.hpp>

#endif /* MAONI_MESH_LOADER_HPP */
