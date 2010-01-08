/*
 * MeshLoader.hpp
 *
 *  Created on: 30.07.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_MESH_LOADER_HPP
#define VMMVIEW_MESH_LOADER_HPP

/**
 * Define a custom MeshLoader.
 *
 * Some description on how to use this macro.
 *
 * \param EXT  The file extension associated with this loader
 * \param NAME The name of the file format.
 */
#define MESH_LOADER(EXT, NAME)                                                 \
	class MeshLoader_##EXT: public MeshLoader                                  \
	{                                                                          \
		const char* const filter() const                                       \
		{                                                                      \
			return #NAME " (*." #EXT ")";                                      \
		}                                                                      \
		const char* const extension() const { return "." #EXT; }               \
		bool load_i(Model& model, const char* filename) const;                 \
	};                                                                         \
	static MeshLoader_##EXT MeshLoader_##EXT##__;                              \
	bool MeshLoader_##EXT::load_i(Model& model, const char* filename) const    \

#include <VMMView/detail/MeshLoader.hpp>

#endif /* VMMVIEW_MESH_LOADER_HPP */
