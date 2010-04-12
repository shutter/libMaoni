/*
 * Channel.cpp
 *
 *  Created on: 26.10.2009
 *      Author: vmml
 */

#include "Channel.hpp"
#include "FrameDataEq.hpp"
#include "Pipe.hpp"

void Channel::frameDraw(uint32_t spin)
{
	eq::Channel::frameDraw(spin);

	const FrameData& framedata =
			static_cast<const Pipe*> (getPipe())->getFrameData();

	framedata.draw();
}
