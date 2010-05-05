/*
 * Channel.hpp
 *
 *  Created on: 05.05.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_CHANNEL_HPP
#define MAONI_EQ_CHANNEL_HPP

#include "EqInclude.hpp"
#include "FrameDataEq.hpp"

class Channel: public eq::Channel
{
public:
	Channel(eq::Window* parent) :
		eq::Channel(parent)
	{
	}

private:
	void frameDraw(const uint32_t spin)
	{
		eq::Channel::frameDraw(spin);

		const FrameData& framedata =
				static_cast<const Node*> (getNode())->getFrameData();

		framedata.draw();
	}
};

#endif /* MAONI_EQ_CHANNEL_HPP */
