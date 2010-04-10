/*
 * pipe.hpp
 *
 *  Created on: 10.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_EQUALIZER_PIPE_HPP
#define VMMVIEW_EQUALIZER_PIPE_HPP

#include "EqInclude.hpp"
#include "ColoredOutput.hpp"
#include "FrameDataEq.hpp"

class Pipe: public eq::Pipe
{
public:
	Pipe(eq::Node* parent, FrameDataEq const& framedata) :
		eq::Pipe(parent), framedata(framedata)
	{
	}

	const FrameData& FrameData() const
	{
		return framedata;
	}

private:
	bool configInit(const uint32_t initID)
	{
		std::cout << RED(initID) << std::endl;

		if (!eq::Pipe::configInit(initID))
			return false;

		getConfig()->mapObject(&framedata, initID);
		return true;
	}

	bool configExit()
	{
		if (!eq::Pipe::configExit())
			return false;

		getConfig()->unmapObject(&framedata);
		return true;
	}

	void frameStart(const uint32_t frameID, const uint32_t frameNumber)
	{
		eq::Pipe::frameStart(frameID, frameNumber);
		framedata.sync();
	}

private:
	FrameDataEq framedata;
};

#endif /* VMMVIEW_EQUALIZER_PIPE_HPP */
