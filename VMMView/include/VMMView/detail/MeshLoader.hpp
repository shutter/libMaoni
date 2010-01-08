/*
 * mesh_loader.hpp
 *
 *  Created on: 07.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_COMMON_MESH_LOADER_HPP
#define VMMVIEW_COMMON_MESH_LOADER_HPP

//#include <istream>
#include <VMMView/detail/Mesh.hpp>
#include <VMMView/detail/Extensible.hpp>
//#include <cstring>

class MeshLoader: public Extensible<MeshLoader>
{
	virtual const char* const filter() const = 0;
	virtual const char* const extension() const = 0;
	virtual bool load_i(Mesh& mesh, const char* filename) const = 0;

public:
	static const char* all_filters();
	static bool load(Mesh& mesh, const char* filename);
};

#endif /* VMMVIEW_COMMON_MESH_LOADER_HPP */
