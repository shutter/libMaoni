/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <eq/eq.h>

#include <Maoni/detail/Algorithm.hpp>
#include "FrameDataEq.hpp"
#include "Channel.hpp"
#include "Config.hpp"
#include "Pipe.hpp"

/*

 In Qt idle func (wie auch immer die heisst)
 if( needsRedraw )
 config->frame()
 post qt redisplay/don't block
 */

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

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	eq::base::Log::level = eq::base::LOG_ERROR;

	NodeFactory node_factory;
	if (!eq::init(argc, argv, &node_factory))
	{
		std::cerr << "\e[0;31mEqualizer init failed\e[m" << std::endl;
		return EXIT_FAILURE;
	}

	Config* config = static_cast<Config*> (eq::getConfig(argc, argv));
	if (!config)
	{
		std::cerr << "\e[0;31mCannot get config\e[m" << std::endl;
		return EXIT_FAILURE;
	}

	// if the application runs as a render slave, it will never get here
	// so don't do any UI stuff until now

	/*
	 createQTGLWidget;
	 _qtWindow = new EqQtWindow( qtGLWidget );
	 mit: class EqQtWindow : public eq::GLWindow { implement abstract functions }
	 makeCurrentNone()
	 */

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
