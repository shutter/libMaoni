/*
 * NodeFactory.hpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#ifndef MAONI_EQ_NODE_FACTORY_HPP
#define MAONI_EQ_NODE_FACTORY_HPP

#include "EqInclude.hpp"
#include "FrameDataEq.hpp"

class NodeFactory: public eq::NodeFactory
{
public:
	NodeFactory(FrameDataEq& framedata) :
		framedata(framedata)
	{
	}

private:
	eq::Channel* createChannel(eq::Window* window);

	eq::Node* createNode(eq::Config* config);

private:
	FrameDataEq& framedata;
};

#endif /* MAONI_EQ_NODE_FACTORY_HPP */
