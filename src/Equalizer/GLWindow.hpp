/*
 * GLWindow.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef GLWINDOW_HPP_
#define GLWINDOW_HPP_

#include "EqInclude.hpp"

class GLWindow: public eq::GLWindow
{
public:
	GLWindow(eq::Window* parent) :
		eq::GLWindow(parent)
	{
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

	void swapBuffers()
	{
	}

	void joinNVSwapBarrier(uint32_t, uint32_t)
	{
	}
};

#endif /* GLWINDOW_HPP_ */
