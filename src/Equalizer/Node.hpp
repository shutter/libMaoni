/*
 * Node.hpp
 *
 *  Created on: 05.05.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_NODE_HPP
#define MAONI_EQ_NODE_HPP

#include "EqInclude.hpp"
#include "FrameDataEq.hpp"

class Node: public eq::Node
{
public:
	Node(eq::Config* config, FrameDataEq const& framedata) :
		eq::Node(config), framedata(framedata)
	{
	}

	const FrameData& getFrameData() const
	{
		return framedata;
	}

private:
	bool configInit(const uint32_t initID)
	{
		if (!eq::Node::configInit(initID))
			return false;

		getConfig()->mapObject(&framedata, initID);
		return true;
	}

	bool configExit()
	{
		if (!eq::Node::configExit())
			return false;

		getConfig()->unmapObject(&framedata);
		return true;
	}

	void frameStart(const uint32_t frameID, const uint32_t frameNumber)
	{
		eq::Node::frameStart(frameID, frameNumber);
		framedata.sync();
	}

private:
	FrameDataEq framedata;
};

#endif /* MAONI_EQ_NODE_HPP */
