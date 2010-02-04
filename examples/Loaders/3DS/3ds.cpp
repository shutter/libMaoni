/*
 * lib3ds.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: aishutter
 */

#include "VMMView/MeshLoader.hpp"
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>

typedef vmml::vector<3, std::size_t> Triangle;

MESH_LOADER(3ds, 3D Studio Max Model)
{
	model.vertices.clear();
	model.triangles.clear();

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
		// copy nodes to triangles
		for (Lib3dsDword i = 0; i < m->faces; i++)
		{
			Lib3dsWord* points = m->faceL[i].points;
			model.triangles.push_back(Triangle(points[0] + offset, points[1]
					+ offset, points[2] + offset));
		}

		// copy vertices
		for (Lib3dsDword i = 0; i < m->points; i++)
		{
			Lib3dsVector& pos = m->pointL[i].pos;

			model.vertices.push_back(Vertex(Vector3(pos[0], pos[1], pos[2]),
					Vector3(0.f), Vector4(0.f), Vector2(0.f)));

			++offset;
		}
	}

	model.calculateNormals();
	model.scale(2.0);

	return true;
}
