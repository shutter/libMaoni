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
#include <GL/gl.h>

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

	//	if (model_changed)
	//	{
	//		broadcast(world, model_name, 0);
	//		if (!master())
	//			load_model(model_name);
	//	}

	//	if (ralgo_changed)
	{
		broadcast(world, ralgo_name, 0);
		if (!master())
			set_render_algorithm(ralgo_name);
	}

	//if(settings_changed)
	if (renderer)
		broadcast(world, *renderer, 0);
}
