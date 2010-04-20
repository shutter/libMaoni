/*
 * NodeFactory.cpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#include "NodeFactory.hpp"
#include "FrameDataEq.hpp"

class Node: public eq::Node
{
public:
	Node(eq::Config* config, FrameDataEq const& framedata) :
		eq::Node(config), framedata(framedata)
	{
	}

	~Node()
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

eq::Channel* NodeFactory::createChannel(eq::Window* window)
{
	return new Channel(window);
}

eq::Node* NodeFactory::createNode(eq::Config* config)
{
	return new Node(config, framedata);
}
