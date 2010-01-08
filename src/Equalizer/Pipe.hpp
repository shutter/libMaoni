/*
 * pipe.hpp
 *
 *  Created on: 10.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_EQUALIZER_PIPE_HPP
#define VMMVIEW_EQUALIZER_PIPE_HPP

#include <eq/client/pipe.h>
#include <eq/client/config.h>

class Pipe: public eq::Pipe
{
public:
	Pipe(eq::Node* parent) :
		eq::Pipe(parent)
	{
	}

	const FrameData& frame_data() const
	{
		return frame_data_;
	}

private:
	bool configInit(const uint32_t initID)
	{
		std::cout << "\e[0;32m" << initID << "\e[m" << std::endl;

		if (!eq::Pipe::configInit(initID))
			return false;

		getConfig()->mapObject(&frame_data_, initID);
		return true;
	}

	bool configExit()
	{
		if (!eq::Pipe::configExit())
			return false;

		getConfig()->unmapObject(&frame_data_);
		return true;
	}

	void frameStart(const uint32_t frameID, const uint32_t frameNumber)
	{
		eq::Pipe::frameStart(frameID, frameNumber);
		frame_data_.sync();
	}

private:
	FrameDataEq frame_data_;
};

#endif /* VMMVIEW_EQUALIZER_PIPE_HPP */
