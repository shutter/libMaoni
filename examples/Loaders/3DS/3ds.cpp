/*
 * lib3ds.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: aishutter
 */

#include <Maoni/MeshLoader.hpp>
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>

typedef vmml::vector<3, std::size_t> Triangle;

MESH_LOADER(3ds, 3D Studio Max Model)
{
	model.clear();

	Lib3dsFile *file = lib3ds_file_load(filename);
	if (!file)
	{
		std::cerr << "***ERROR***\nLoading file failed: " << filename
				<< std::endl;
		return false;
	}

	int offset = 0;
	for (Lib3dsMesh* m = file->meshes; m; m = m->next)
	{
		// copy vertices
		for (Lib3dsDword i = 0; i < m->points; i++)
		{
			Lib3dsVector& pos = m->pointL[i].pos;

			model.add_vertex(Vertex(Vector3(pos[0], pos[1], pos[2]),
					Vector3(0.f), Color(), Vector2(0.f)));

			++offset;
		}

		// copy nodes to triangles
		for (Lib3dsDword i = 0; i < m->faces; i++)
		{
			Lib3dsWord* points = m->faceL[i].points;
			model.add_triangle(points[0] + offset, points[1] + offset, points[2] + offset);
		}
	}

	model.calculate_normals();
	model.fix_scale();

	return true;
}
