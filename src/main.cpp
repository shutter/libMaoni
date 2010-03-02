/*
 * Author: dpfeifer
 */

#include <Maoni.hpp>

int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack);

int main(int argc, char* argv[])
{
	return maoni_main(argc, argv, AlgorithmFactory::stack, MeshLoader::stack);
}
