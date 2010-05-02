/*
 * RenderWidget.cpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#include "RenderWidget.hpp"

RenderWidgetEq::RenderWidgetEq(FrameData& framedata, eq::Config* config) :
	RenderWidget(framedata), config(config)
{
}

RenderWidgetEq::~RenderWidgetEq()
{
}

/*
 * In Qt idle func (wie auch immer die heisst)
 * if( needsRedraw )
 * config->frame()
 * post qt redisplay/don't block
 */

void RenderWidgetEq::paintGL()
{
	preDraw();
	draw();
	postDraw();

//	framedata.commit();
//	config->startFrame(0);
//	config->finishFrame();
}
