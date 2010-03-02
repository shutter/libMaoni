/*
 * mesh_loader.cpp
 *
 *  Created on: 18.10.2009
 *      Author: daniel
 */

#include <Maoni/detail/MeshLoader.hpp>
#include <boost/algorithm/string/predicate.hpp>

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
