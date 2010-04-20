/*
 * Window.hpp
 *
 *  Created on: 29.03.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_WINDOW_HPP
#define MAONI_EQ_WINDOW_HPP

#include "EqInclude.hpp"

eq::base::Lockable<eq::Window*> _qtWindow = 0;

class Window: public eq::Window
{

private:

	bool configInitOSWindow(const uint32_t initID);

	//! eq::Window used by the first Window::configInitOSWindow() call
	static eq::base::Lockable<eq::Window*> _qtWindow;
};

#endif /* MAONI_EQ_WINDOW_HPP */
