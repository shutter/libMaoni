/*
 * MeshLoader.hpp
 *
 *  Created on: 30.07.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_MESH_LOADER_HPP
#define VMMVIEW_MESH_LOADER_HPP


#define MESH_LOADER(EXT, NAME)                                                 \
	class MeshLoader_##EXT: public MeshLoader                                  \
	{                                                                          \
		const char* const filter() const                                       \
		{                                                                      \
			return #NAME " (*." #EXT ")";                                      \
		}                                                                      \
		const char* const extension() const { return "." #EXT; }               \
		bool load_i(Mesh& mesh, const char* filename) const;                   \
	};                                                                         \
	static MeshLoader_##EXT MeshLoader_##EXT##__;                              \
	bool MeshLoader_##EXT::load_i(Mesh& mesh, const char* filename) const

#include <VMMView/detail/MeshLoader.hpp>

#endif /* VMMVIEW_MESH_LOADER_HPP */
