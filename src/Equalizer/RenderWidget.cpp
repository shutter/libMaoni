/*
 * RenderWidget.cpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#include "RenderWidget.hpp"
#include "Node.hpp"

void RenderWidgetEq::glDraw()
{
	// framedata.commit();
	config->startFrame(0);
	config->finishFrame();
}

void RenderWidgetEq::static_draw(eq::Channel* channel)
{
	static_cast<const Node*> (channel->getNode())->getFrameData().draw();
}

void RenderWidgetEq::init()
{

}
