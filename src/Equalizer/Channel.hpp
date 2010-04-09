/*
 * Channel.hpp
 *
 *  Created on: 31.07.2009
 *      Author: daniel
 */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <eq/client/channel.h>

class Channel: public eq::Channel
{
public:
	Channel(eq::Window* parent) :
		eq::Channel(parent)
	{
	}

private:
	void frameDraw(uint32_t spin);
};

#endif /* CHANNEL_HPP */
