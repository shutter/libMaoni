/*
 * mesh_loader.hpp
 *
 *  Created on: 07.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_COMMON_MESH_LOADER_HPP
#define VMMVIEW_COMMON_MESH_LOADER_HPP

#include <Maoni/Model.hpp>
#include <Maoni/detail/Extensible.hpp>

class MeshLoader: public Extensible<MeshLoader>
{
	virtual const char* const filter() const = 0;
	virtual const char* const extension() const = 0;
	virtual bool load_i(Model& mesh, const char* filename) const = 0;

public:
	static const char* all_filters();
	static bool load(Model& mesh, const char* filename);
};

#endif /* VMMVIEW_COMMON_MESH_LOADER_HPP */
