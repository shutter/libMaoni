/*
 * lib3ds.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: aishutter
 */

#include <Maoni/MeshLoader.hpp>
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <stdexcept>
#include <iostream>

MESH_LOADER(3ds, 3D Studio Max Model)
{
	model->clear();

	Lib3dsFile *file = lib3ds_file_load(filename);
	if (!file)
		throw std::runtime_error("Loading file failed");

	unsigned int offset = 0;

		for (Lib3dsMesh* mesh = file->meshes; mesh != NULL; mesh = mesh->next)
		{
			// copy vertices
			for (Lib3dsDword i = 0; i < mesh->points; i++)
			{
				Lib3dsVector& pos = mesh->pointL[i].pos;

				model->add_vertex(Vertex(pos[0], pos[1], pos[2]));

			}

			// copy nodes to triangles
			for (Lib3dsDword i = 0; i < mesh->faces; i++)
			{
				Lib3dsWord* points = mesh->faceL[i].points;
				model->add_triangle(points[0] + offset, points[1] + offset, points[2] + offset);
			}

			offset += mesh->points;
		}

	model->calculate_normals();
	model->fix_scale();
	model->generate_vbo();
}
