/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "FrameData.hpp"
#include <boost/mpi/collectives.hpp>
#include "../Common/serialize.hpp"
#include <GL/ice-t_mpi.h>
#include <GL/gl.h>

FrameDataIceT::FrameDataIceT(RenderAlgorithm* algorithm_stack,
	MeshLoader* mesh_loader_stack) :
	FrameData(algorithm_stack, mesh_loader_stack), //
		world(), tiles(world.size())
{
	int rows = sqrt(tiles.size());
	for (std::size_t i = 0; i < tiles.size(); ++i)
	{
		int col = i / rows;
		int row = i % rows;

		tiles[i].visible = true; //i == 0;

		tiles[i].x = col * 640;
		tiles[i].y = row * 480;
	}
}

FrameDataIceT::~FrameDataIceT()
{
}

void FrameDataIceT::animate()
{
	double matrix[16];

	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	broadcast(world, matrix, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);

	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
	broadcast(world, matrix, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(matrix);

	// TODO: if(tiles_changed)
	{
		broadcast(world, tiles, 0);

		int w, h;
		icetResetTiles();
		for (std::size_t i = 0; i < tiles.size(); ++i)
		{
			Tile& tile = tiles[0];

			//if (tile.visible)
			//{
			w = width;
			h = height;
			broadcast(world, w, i);
			broadcast(world, h, i);
			icetAddTile(tile.x, tile.y, w, h, i);
			//}

			if (i == world.rank())
			{
				icetBoundingBoxf( //
					tile.min.data[0], tile.max.data[0], //
					tile.min.data[1], tile.max.data[1], //
					tile.min.data[2], tile.max.data[2]);
			}
		}
	}

	//TODO: if (model_changed)
	//	{
	//		broadcast(world, model_name, 0);
	//		if (!master())
	//			load_model(model_name);
	//	}

	//TODO: if (ralgo_changed)
	{
		broadcast(world, ralgo_name, 0);
		if (!master())
			set_render_algorithm(ralgo_name);
	}

	//TODO: if(settings_changed)
	if (renderer)
		broadcast(world, *renderer, 0);
}

void FrameDataIceT::resize(int w, int h)
{
	width = w;
	height = h;
}
