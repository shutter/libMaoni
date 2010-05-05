/*
 * GLWindow.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_GLWINDOW_HPP
#define MAONI_EQ_GLWINDOW_HPP

#include "EqInclude.hpp"
#include <QGLWidget>

class GLWindow: public eq::GLWindow
{
public:
	GLWindow(eq::Window* window, QGLWidget* qglwidget) :
		eq::GLWindow(window), qglwidget(qglwidget)
	{
		makeCurrent();
	}

	~GLWindow()
	{
	}

private:
	bool configInit()
	{
		return true;
	}

	void configExit()
	{
	}

	void makeCurrent() const
	{
		qglwidget->makeCurrent();
	}

	void swapBuffers()
	{
		qglwidget->swapBuffers();
	}

	void joinNVSwapBarrier(uint32_t, uint32_t)
	{
	}

private:
	QGLWidget* qglwidget;
};

#endif /* MAONI_EQ_GLWINDOW_HPP */
