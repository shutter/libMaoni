/*
 * RenderWidget.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_RENDER_WIDGET_HPP
#define MAONI_EQ_RENDER_WIDGET_HPP

#include "../Widgets/RenderWidget.hpp"
//#include "EqInclude.hpp"

namespace eq
{
class Config;
}

class RenderWidgetEq: RenderWidget
{
public:
	RenderWidgetEq(FrameData& framedata, eq::Config* config);
	~RenderWidgetEq();

private:
	void paintGL();

private:
	eq::Config* config;
};

#endif /* MAONI_EQ_RENDER_WIDGET_HPP */
