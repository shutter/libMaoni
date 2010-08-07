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

#ifndef MAONI_ICET_RENDERWIDGET_HPP
#define MAONI_ICET_RENDERWIDGET_HPP

#include "../Common/RenderWidget.hpp"
#include "FrameData.hpp"
#include <GL/ice-t.h>

class RenderWidgetIceT: public RenderWidget
{
public:
	RenderWidgetIceT(FrameData& framedata);

	~RenderWidgetIceT();

private:
	void paintGL();
	void stopAnimation();
	void resizeWindow();

private:
	IceTContext context;
	FrameDataIceT& framedata_icet;
	static RenderWidgetIceT* singleton;
	static void static_draw();
};

#endif /* MAONI_ICET_RENDERWIDGET_HPP */
