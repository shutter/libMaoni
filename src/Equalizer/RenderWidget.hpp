/*
 * RenderWidget.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_RENDER_WIDGET_HPP
#define MAONI_EQ_RENDER_WIDGET_HPP

#include "EqInclude.hpp"
#include "../Common/RenderWidget.hpp"
#include <eQute.hpp>

class RenderWidgetEq: public RenderWidget, public eQute<RenderWidgetEq>::WidgetBase
{
public:
	RenderWidgetEq(FrameData& framedata, eq::Config* config) :
		RenderWidget(framedata), config(config)
	{
	}

	using QGLViewer::paintGL;

	static void static_draw(eq::Channel* channel);
	void init();

private:
	void glDraw();

private:
	eq::Config* config;
};

#endif /* MAONI_EQ_RENDER_WIDGET_HPP */
