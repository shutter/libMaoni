/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include "EqInclude.hpp"

#include <Maoni/detail/Algorithm.hpp>
#include "FrameDataEq.hpp"
#include "Channel.hpp"
#include "Pipe.hpp"
#include "ColoredOutput.hpp"

/*

 In Qt idle func (wie auch immer die heisst)
 if( needsRedraw )
 config->frame()
 post qt redisplay/don't block
 */

class NodeFactory: public eq::NodeFactory
{
public:
	NodeFactory(FrameDataEq& framedata) :
		framedata(framedata)
	{
	}

private:
	eq::Channel* createChannel(eq::Window* window)
	{
		return new Channel(window);
	}

	eq::Pipe* createPipe(eq::Node* node)
	{
		return new Pipe(node, framedata);
	}

private:
	FrameDataEq& framedata;
};

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	eq::base::Log::level = eq::base::LOG_ERROR;

	FrameDataEq framedata(algorithm_factory_stack, mesh_loader_stack);

	NodeFactory node_factory(framedata);
	if (!eq::init(argc, argv, &node_factory))
	{
		std::cerr << RED("Equalizer init failed") << std::endl;
		return EXIT_FAILURE;
	}

	eq::Config* config = eq::getConfig(argc, argv);
	if (!config)
	{
		std::cerr << RED("Cannot get config") << std::endl;
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

	config->registerObject(&framedata);

	if (!config->init(framedata.getID()))
	{
		std::cerr << "Config initialization failed: "
				<< config->getErrorMessage() << std::endl;
		return EXIT_FAILURE;
	}

	uint32_t spin = 0;
	while (config->isRunning())
	{
		framedata.commit();
		config->startFrame(++spin);
		config->finishFrame();
	}

	config->deregisterObject(&framedata);

	config->exit();
	eq::releaseConfig(config);
	eq::exit();

	return EXIT_SUCCESS;
}
