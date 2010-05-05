/*
 * NodeFactory.cpp
 *
 *  Created on: 20.04.2010
 *      Author: daniel
 */

#include "NodeFactory.hpp"
#include "FrameDataEq.hpp"

#include "Node.hpp"
#include "Channel.hpp"
#include "Window.hpp"

eq::Node* NodeFactory::createNode(eq::Config* config)
{
	return new Node(config, framedata);
}

eq::Window* NodeFactory::createWindow(eq::Pipe* pipe)
{
	return new EqWindow(pipe);
}

eq::Channel* NodeFactory::createChannel(eq::Window* window)
{
	return new Channel(window);
}

