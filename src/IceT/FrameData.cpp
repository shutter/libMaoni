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
			world(), tiles(world.size()), strategy_(3)
{
	render_context_width = 1024;
	render_context_height = 768;

	change = 0;

	int rows = sqrt(tiles.size());
	std::cout << "rows: " << rows << std::endl;
	for (std::size_t i = 0; i < tiles.size(); ++i)
	{
		int col = i / rows;
		int row = i % rows;

		if (i == 0)
			tiles[i].visible = true;

		tiles[i].x = 0;//col * 640;
		tiles[i].y = 0;//row * 480;
	}
}

FrameDataIceT::~FrameDataIceT()
{
}

void FrameDataIceT::animate()
{
	broadcast(world, change, 0);
	double matrix[16];

	/*	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	 broadcast(world, matrix, 0);
	 glMatrixMode( GL_PROJECTION);
	 glLoadMatrixd(matrix);*/

	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
	broadcast(world, matrix, 0);
	glMatrixMode( GL_MODELVIEW);
	glLoadMatrixd(matrix);

	if (change & TILES_CHANGED)
	{
		setDoResize(true);

		broadcast(world, tiles, 0);

		icetResetTiles();
		for (std::size_t i = 0; i < tiles.size(); ++i)
		{
			Tile& tile = tiles[i];

			//if (tile.visible)
			{
				icetAddTile(tile.x, tile.y, tile.sx, tile.sy, i);
			}

			//if (i == world.rank())
			{
				icetBoundingBoxf( //
						tile.min.data[0], tile.max.data[0], //
						tile.min.data[1], tile.max.data[1], //
						tile.min.data[2], tile.max.data[2]);
			}
		}

		icetGetIntegerv(ICET_TILE_MAX_WIDTH, &render_context_width);
		icetGetIntegerv(ICET_TILE_MAX_HEIGHT, &render_context_height);
		std::cout << "tiles changed" << std::endl;
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

		std::cout << "strategy changed to " << strategy_ << std::endl;
	}

	if (change & LIGHT_CHANGED)
	{
		broadcast(world, lights, 0);
		std::cout << "light changed" << std::endl;
	}

	if (change & MODEL_CHANGED)
	{
		broadcast(world, model_name, 0);
		if (!master())
			load_model(model_name.c_str());
		std::cout << "model changed" << std::endl;
	}

	if (change & RENDERER_CHANGED)
	{
		broadcast(world, ralgo_name, 0);
		if (!master())
			set_render_algorithm(ralgo_name);
		std::cout << "renderer changed" << std::endl;
	}

	if (change & RENDERPARAM_CHANGED)
	{
		if (renderer)
			broadcast(world, *renderer, 0);
		std::cout << "renderparameter changed" << std::endl;
	}

	change = 0;
}

void FrameDataIceT::resize(int w, int h)
{
	FrameData::resize(w, h);
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
