/*
 * RenderWidget.cpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#include "RenderWidget.hpp"

eq::base::Lockable<RenderWidgetEq*> RenderWidgetEq::instance_;

RenderWidgetEq::RenderWidgetEq(FrameData& framedata, eq::Config* config) :
	RenderWidget(framedata), config(config)
{
	instance_ = this;

	// make no context current
	doneCurrent();
}

RenderWidgetEq::~RenderWidgetEq()
{
}

RenderWidgetEq* RenderWidgetEq::instance()
{
	eq::base::ScopedMutex lock(instance_);

	RenderWidgetEq* tmp = instance_.data;
	instance_ = 0;
	return tmp;
}

void RenderWidgetEq::paintGL()
{
	//	preDraw();
	//	draw();
	//	postDraw();

	// TODO:
	// if(needs redraw)
	// {
	// framedata.commit();
	config->startFrame(0);
	config->finishFrame();
	// }
	// post qt redisplay/don't block
}
