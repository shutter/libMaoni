/*
 * Config.hpp
 *
 *  Created on: 31.07.2009
 *      Author: daniel
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <eq/client/client.h>
#include <eq/client/server.h>
#include <eq/client/config.h>
#include "FrameDataEq.hpp"

class Config: public eq::Config
{
public:
	Config(eq::ServerPtr parent) :
		eq::Config(parent), dragging(false)
	{
	}

private:
	bool handleEvent(const eq::ConfigEvent* event);
	void mouse_update(const eq::ConfigEvent* event);

private:
	int last_x;
	int last_y;
	float lastquat[4];
	bool dragging;

public:
	FrameDataEq frame_data;
};

#endif /* CONFIG_HPP */
