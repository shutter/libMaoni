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
#include <Maoni/glew.h>
#include <boost/mpi/collectives.hpp>
#include "../Common/serialize.hpp"
#include <GL/ice-t_mpi.h>

FrameDataIceT::FrameDataIceT(RenderAlgorithm* algorithm_stack,
		MeshLoader* mesh_loader_stack) :
	FrameData(algorithm_stack, mesh_loader_stack), //
			world(), tiles(world.size()), strategy_(3), //
			replication_group_(false), change(127)
{
	render_context_width = tiles[0].sx;
	render_context_height = tiles[0].sy;

	int rows = sqrt(static_cast<float> (tiles.size()));

	// Tile 0 shows the whole model, the others
	// only the part they render themselves
	tiles[0].visible = true;

	// Take the square number >= number of tiles
	// fill the square with actual number of tiles from
	// left to right, bottom to top
	for (std::size_t i = 0; i < tiles.size(); ++i)
	{
		int col = i / rows;
		int row = i % rows;

		tiles[i].x = col * render_context_width;
		tiles[i].y = row * render_context_height;
	}
}

FrameDataIceT::~FrameDataIceT()
{
}

void FrameDataIceT::setMatrices()
{
	glGetDoublev(GL_PROJECTION_MATRIX, matrix.begin());
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix.begin() + 16);

	broadcast(world, matrix, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix.begin());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(matrix.begin() + 16);
}

void FrameDataIceT::setTiles()
{
	setDoResize(true);

	broadcast(world, tiles, 0);

	icetResetTiles();
	for (std::size_t i = 0; i < tiles.size(); ++i)
	{
		Tile & tile = tiles[i];
		if (tile.visible)
		{
			icetAddTile(tile.x, tile.y, tile.sx, tile.sy, i);
		}

		{
			icetBoundingBoxf( //
					tile.min_box.data[0], tile.max_box.data[0], //
					tile.min_box.data[1], tile.max_box.data[1], //
					tile.min_box.data[2], tile.max_box.data[2]);
		}
	}

	icetGetIntegerv(ICET_TILE_MAX_WIDTH, &render_context_width);
	icetGetIntegerv(ICET_TILE_MAX_HEIGHT, &render_context_height);
}

void FrameDataIceT::animate()
{
	broadcast(world, change, 0);

	if (change & TILES_CHANGED)
	{
		calcGlobalDisplaySize();
		setTiles();
	}

	if (change & STRATEGY_CHANGED)
	{
		broadcast(world, strategy_, 0);

		switch (strategy_)
		{
		case 0:
			icetStrategy(ICET_STRATEGY_DIRECT);
			break;
		case 1:
			icetStrategy(ICET_STRATEGY_SERIAL);
			break;
		case 2:
			icetStrategy(ICET_STRATEGY_SPLIT);
			break;
		case 3:
			icetStrategy(ICET_STRATEGY_REDUCE);
			break;
		case 4:
			icetStrategy(ICET_STRATEGY_VTREE);
			break;
		default:
			icetStrategy(ICET_STRATEGY_REDUCE);
		}
	}

	if (change & LIGHT_CHANGED)
	{
		broadcast(world, lights, 0);
	}

	if (change & MODEL_CHANGED)
	{
		broadcast(world, model_name, 0);
		if (!master())
			load_model(model_name.c_str());
	}

	if (change & RENDERER_CHANGED)
	{
		broadcast(world, ralgo_name, 0);
		if (!master())
			set_render_algorithm(ralgo_name);
	}

	if (change & RENDERPARAM_CHANGED)
	{
		if (renderer)
			broadcast(world, *renderer, 0);
	}

	if (change & REPLICATE_CHANGED)
	{
		broadcast(world, replication_group_, 0);
		if (replication_group_)
		{
			// all the ranks build groups as defined by RenderGroup in the
			// render widget - default value is zero, so every rank has
			// the same data: the whole model (use e.g. for display walls)
			icetDataReplicationGroupColor(tiles[myrank()].render_group);
		}
		else
		{
			// if there is no replicated data, every rank builds its own group
			icetDataReplicationGroupColor(myrank());
		}
	}
	change = 0;
}

void FrameDataIceT::resize(int w, int h)
{
	FrameData::resize(w, h);
}

/*
 * Calculates the global display size from all the tiles'
 * size and offset values. IceT does not provide this values
 * itself.
 */
void FrameDataIceT::calcGlobalDisplaySize()
{
	global_display_size.min_x = 0;
	global_display_size.min_y = 0;
	global_display_size.max_x = 0;
	global_display_size.max_y = 0;

	for (size_t i = 0; i < tiles.size(); ++i)
	{
		if (tiles[i].visible)
		{
			// search min x - the min offset
			global_display_size.min_x = std::min(global_display_size.min_x,
					tiles[i].x);
			// search min y - the min offset
			global_display_size.min_y = std::min(global_display_size.min_y,
					tiles[i].y);
			// search max x - the max offset plus size
			global_display_size.max_x = std::max(global_display_size.max_x,
					tiles[i].x + tiles[i].sx);
			// search max y - the max offset plus size
			global_display_size.max_y = std::max(global_display_size.max_y,
					tiles[i].y + tiles[i].sy);
		}
	}

	global_display_size.size_x = (global_display_size.max_x
			- global_display_size.min_x);
	global_display_size.size_y = (global_display_size.max_y
			- global_display_size.min_y);
}

void FrameDataIceT::do_import_scene(boost::archive::xml_iarchive& archive)
{
	archive >> boost::serialization::make_nvp("tiles", tiles);

	FrameData::do_import_scene(archive);
}

void FrameDataIceT::do_export_scene(boost::archive::xml_oarchive& archive)
{
	archive << boost::serialization::make_nvp("tiles", tiles);

	FrameData::do_export_scene(archive);
}

void FrameDataIceT::setStrategy(int strategy)
{
	strategy_ = strategy;
	setStrategyChanged();
}

void FrameDataIceT::setReplicate(bool replicate)
{
	replication_group_ = replicate;
	setReplicateChanged();
}
