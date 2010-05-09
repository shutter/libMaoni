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

#include "RenderWidget.hpp"
#include <GL/ice-t_mpi.h>
#include <boost/assert.hpp>

RenderWidgetIceT* RenderWidgetIceT::singleton = 0;

RenderWidgetIceT::RenderWidgetIceT(FrameData& framedata) :
	RenderWidget(framedata)
{
	BOOST_ASSERT(!singleton && "Only one Instance of IceTWidget may exist");
	singleton = this;

	IceTCommunicator communicator = icetCreateMPICommunicator(MPI_COMM_WORLD);
	context = icetCreateContext(communicator);
	icetDestroyMPICommunicator(communicator);

	icetStrategy(ICET_STRATEGY_REDUCE);
	icetDrawFunc(static_draw);

	icetResetTiles();

	int WINDOW_HEIGHT = 250;
	int WINDOW_WIDTH  = 250;
//	icetAddTile(0, 0, 500, 500, 0);

	icetAddTile(0,           WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	icetAddTile(WINDOW_WIDTH,WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
	icetAddTile(0,           0,             WINDOW_WIDTH, WINDOW_HEIGHT, 2);
	icetAddTile(WINDOW_WIDTH,0,             WINDOW_WIDTH, WINDOW_HEIGHT, 3);
}

RenderWidgetIceT::~RenderWidgetIceT()
{
	icetDestroyContext(context);
}

void RenderWidgetIceT::static_draw()
{
	singleton->RenderWidget::draw();
}

void RenderWidgetIceT::paintGL()
{
	preDraw();
	icetDrawFrame();
	postDraw();

	// if(rank() != 0)
	// 	updateGL();
}
