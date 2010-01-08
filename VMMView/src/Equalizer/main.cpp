/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <eq/eq.h>

#include <FL/Fl.H>

#include "Common/ConfigWindow.hpp"
#include <VMMView/detail/Algorithm.hpp>
#include "FrameDataEq.hpp"
#include "Channel.hpp"
#include "Config.hpp"
#include "Pipe.hpp"

#include <eq/client/nodeFactory.h>
#include <eq/client/init.h>

struct NodeFactory: eq::NodeFactory
{
	eq::Channel* createChannel(eq::Window* parent)
	{
		return new Channel(parent);
	}

	eq::Config* createConfig(eq::ServerPtr parent)
	{
		return new Config(parent);
	}

	eq::Pipe* createPipe(eq::Node* parent)
	{
		return new Pipe(parent);
	}
};

int main(int argc, char* argv[])
{
	eq::base::Log::level = eq::base::LOG_ERROR;

	NodeFactory node_factory;
	if (!eq::init(argc, argv, &node_factory))
	{
		std::cerr << "\e[0;31mEqualizer init failed\e[m" << std::endl;
		return EXIT_FAILURE;
	}

	Config* config = static_cast<Config*>(eq::getConfig(argc, argv));
	if (!config)
	{
		std::cerr << "\e[0;31mCannot get config\e[m" << std::endl;
		return EXIT_FAILURE;
	}

	// if the application runs as a render slave, it will never get here
	// so dont do any UI stuff until now

	//Fl::scheme("gtk+");

	ConfigWindow config_window(config->frame_data);

	config->registerObject(&config->frame_data);

	if (!config->init(config->frame_data.getID()))
	{
		std::cerr << "Config initialization failed: "
				<< config->getErrorMessage() << std::endl;
		return EXIT_FAILURE;
	}

	uint32_t spin = 0;
	while (config->isRunning() && Fl::check())
	{
		config->frame_data.commit();
		config->startFrame(++spin);
		config->finishFrame();
	}

	config->deregisterObject(&config->frame_data);

	config->exit();
	eq::releaseConfig(config);
	eq::exit();

	return EXIT_SUCCESS;
}
