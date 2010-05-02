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

#include <Maoni/detail/Algorithm.hpp>
#include "FrameDataEq.hpp"
#include "GLWindow.hpp"
#include "NodeFactory.hpp"
#include "../Widgets/MainWindow.hpp"
#include "RenderWidget.hpp"

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

	QPixmap pixmap(":/Maoni/Splashscreen.png");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    splash.showMessage("Loading Widgets...");
	QTimer::singleShot(3000, &splash, SLOT(close()));

	/*
	 createQTGLWidget;
	 _qtWindow = new EqQtWindow( qtGLWidget );
	 mit: class EqQtWindow : public eq::GLWindow { implement abstract functions }
	 makeCurrentNone()
	 */

	MainWindow main_window(framedata, new RenderWidget(framedata));
	main_window.setWindowTitle("MaoniEq");

	config->registerObject(&framedata);

	if (!config->init(framedata.getID()))
	{
		std::cerr << "Config initialization failed: "
				<< config->getErrorMessage() << std::endl;
		return EXIT_FAILURE;
	}

	main_window.show();

	uint32_t spin = 0;
	while (config->isRunning())
	{
		framedata.commit();
		config->startFrame(++spin);
		config->finishFrame();
	}

	int retval = app.exec();

	config->deregisterObject(&framedata);

	config->exit();
	eq::releaseConfig(config);
	eq::exit();

	return retval;
}
