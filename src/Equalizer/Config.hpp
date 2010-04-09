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

struct Config: eq::Config
{
	Config(eq::ServerPtr parent) :
		eq::Config(parent)
	{
	}

	FrameDataEq frame_data;
};

#endif /* CONFIG_HPP */
