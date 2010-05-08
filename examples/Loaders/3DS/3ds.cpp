/*
 * lib3ds.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: aishutter
 */

#include <Maoni/MeshLoader.hpp>
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <iostream>

MESH_LOADER(3ds, 3D Studio Max Model)
{
	model.clear();

	Lib3dsFile *file = lib3ds_file_load(filename);
	if (!file)
		throw std::runtime_error("Loading file failed");

	int offset = 0;
	for (Lib3dsMesh* m = file->meshes; m; m = m->next)
	{
		// copy vertices
		for (Lib3dsDword i = 0; i < m->points; i++)
		{
			Lib3dsVector& pos = m->pointL[i].pos;

			model.add_vertex(Vertex(pos[0], pos[1], pos[2]));

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
}
