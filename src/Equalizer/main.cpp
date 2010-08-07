/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include "EqInclude.hpp"
#include <eQute.hpp>

#include <Maoni/RenderAlgorithm.hpp>
#include "FrameDataEq.hpp"
#include "Node.hpp"
#include "../Common/MainWindow.hpp"
#include "RenderWidget.hpp"

class NodeFactory: public eQute<RenderWidgetEq>::Factory
{
public:
	NodeFactory(FrameDataEq& framedata) :
		framedata(framedata)
	{
	}

private:
	eq::Node* createNode(eq::Config* config)
	{
		return new Node(config, framedata);
	}

private:
	FrameDataEq& framedata;
};

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[], //
		RenderAlgorithm* algorithm_stack, MeshLoader* mesh_loader_stack)
{
	eq::base::Log::level = eq::base::LOG_ERROR;

	FrameDataEq framedata(algorithm_stack, mesh_loader_stack);

	NodeFactory node_factory(framedata);
	if (!eq::init(argc, argv, &node_factory))
	{
		std::cerr << "Equalizer init failed" << std::endl;
		return EXIT_FAILURE;
	}

	eq::Config* config = eq::getConfig(argc, argv);
	if (!config)
	{
		std::cerr << "Cannot get config" << std::endl;
		return EXIT_FAILURE;
	}

	// if the application runs as a render slave, it will never get here
	// so don't do any UI stuff until now

	QApplication app(argc, argv);
	Q_INIT_RESOURCE(Resources);

	QPixmap pixmap(":/Maoni/Splashscreen.jpg");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
	splash.show();

	MainWindow main_window(framedata, new RenderWidgetEq(framedata, config));
	main_window.setWindowTitle("Maoni using Equalizer Parallel Rendering");

	config->registerObject(&framedata);

	if (!config->init(framedata.getID()))
	{
		std::cerr << "Config initialization failed: "
				<< config->getErrorMessage() << std::endl;
		return EXIT_FAILURE;
	}

	QTimer::singleShot(1000, &main_window, SLOT(show()));
	QTimer::singleShot(1337, &splash, SLOT(close()));

	int retval = app.exec();

	config->deregisterObject(&framedata);

	config->exit();
	eq::releaseConfig(config);
	eq::exit();

	return retval;
}
