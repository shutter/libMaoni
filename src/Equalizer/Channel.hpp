/*
 * Channel.hpp
 *
 *  Created on: 31.07.2009
 *      Author: daniel
 */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "EqInclude.hpp"

class Channel: public eq::Channel
{
public:
	Channel(eq::Window* parent) :
		eq::Channel(parent)
	{
	}

private:
	void frameDraw(const uint32_t spin);
};

#endif /* CHANNEL_HPP */
