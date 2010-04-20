/*
 * RenderWidget.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_RENDER_WIDGET_HPP
#define MAONI_EQ_RENDER_WIDGET_HPP

#include "../Widgets/RenderWidget.hpp"

class RenderWidgetEq: RenderWidget
{
public:
	RenderWidgetEq();
	~RenderWidgetEq();

private:
	void paintGL();
};

#endif /* MAONI_EQ_RENDER_WIDGET_HPP */
