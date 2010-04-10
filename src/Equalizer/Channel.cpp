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

	const FrameData& frame_data =
			static_cast<const Pipe*> (getPipe())->FrameData();
}
