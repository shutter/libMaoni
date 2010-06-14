/*
 * Author: dpfeifer
 */

#include <Maoni.hpp>

#ifdef _MSC_VER
__declspec(dllimport)
#endif
int maoni_main(int argc, char* argv[],
		RenderAlgorithm* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack);

int main(int argc, char* argv[])
{
	return maoni_main(argc, argv, RenderAlgorithm::stack, MeshLoader::stack);
}
