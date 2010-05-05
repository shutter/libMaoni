/*
 * Window.hpp
 *
 *  Created on: 05.05.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_WINDOW_HPP
#define MAONI_EQ_WINDOW_HPP

#include "EqInclude.hpp"
#include "FrameDataEq.hpp"

class EqWindow: public eq::Window
{
public:
	EqWindow(eq::Pipe* parent) :
		eq::Window(parent)
	{
	}

private:
	bool configInitOSWindow(const uint32_t id);
};

#endif /* MAONI_EQ_WINDOW_HPP */
