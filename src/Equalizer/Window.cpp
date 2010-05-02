///*
// * Window.cpp
// *
// *  Created on: 29.03.2010
// *      Author: daniel
// */
//
//#include "Window.hpp"
//
////! eq::Window used by the first Window::configInitOSWindow() call
//eq::base::Lockable<eq::Window*> Window::_qtWindow = 0;
//
//bool Window::configInitOSWindow(const uint32_t initID)
//{
//	if (_qtWindow != 0)
//	{
//		eq::base::ScopedMutex lock(_qtWindow);
//		_qtWindow->makeCurrent(); // < implement this
//		_qtWindow->initGLEW();
//		setOSWindow(_qtWindow.data);
//		_qtWindow = 0;
//	}
//	else
//	{
//		eq::Window::configInitOSWindow();
//	}
//}
