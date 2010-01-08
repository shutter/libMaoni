/*
 * mesh_loader.cpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
 */

#include <VMMView/detail/MeshLoader.hpp>
#include <cstring>

const char* MeshLoader::all_filters()
{
	static std::string instance;

	if (instance.empty())
	{
		instance = "All files (*.*)";
		for (MeshLoader* i = stack; i; i = i->next)
		{
			instance += ";;";
			instance += i->filter();
		}
	}

	return instance.c_str();
}

bool MeshLoader::load(Model& mesh, const char* filename)
{
	for (MeshLoader* i = stack; i; i = i->next)
	{
		const char* extension = std::strrchr(filename, '.');
		if (!strcasecmp(extension, i->extension()))
			return i->load_i(mesh, filename);
	}

	return false;
}
