/*
 * Window.cpp
 *
 *  Created on: 05.05.2010
 *      Author: daniel
 */

#include "Window.hpp"
#include "GLWindow.hpp"
#include "RenderWidget.hpp"

bool EqWindow::configInitOSWindow(const uint32_t id)
{
	QGLWidget* qglwidget = RenderWidgetEq::instance();

	if (!qglwidget)
		return eq::Window::configInitOSWindow(id);

	setOSWindow(new GLWindow(this, qglwidget));
	return true;
}
