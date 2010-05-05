/*
 * RenderWidget.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_RENDER_WIDGET_HPP
#define MAONI_EQ_RENDER_WIDGET_HPP

#include "EqInclude.hpp"
#include "../Widgets/RenderWidget.hpp"

class RenderWidgetEq: public RenderWidget
{
public:
	RenderWidgetEq(FrameData& framedata, eq::Config* config);
	~RenderWidgetEq();

	static RenderWidgetEq* instance();

private:
	void paintGL();

private:
	eq::Config* config;

	static eq::base::Lockable<RenderWidgetEq*> instance_;
};

#endif /* MAONI_EQ_RENDER_WIDGET_HPP */
