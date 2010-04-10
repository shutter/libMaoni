/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <QApplication>
#include <QSplashScreen>
#include "../Common/FrameData.hpp"
#include "../Widgets/MainWindow.hpp"
#include "../Widgets/RenderWidget.hpp"

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	QApplication app(argc, argv);

	QSplashScreen splash(QPixmap("libmaoni_sscr.png"), Qt::WindowStaysOnTopHint);
    splash.show();
    splash.showMessage("Loading Widgets...");

	FrameData framedata(algorithm_factory_stack, mesh_loader_stack);

	MainWindow main_window(framedata, new RenderWidget(framedata));
	main_window.setWindowTitle("Maoni");
	main_window.show();

	QTimer::singleShot(3000, &splash, SLOT(close()));
    //splash.finish(&main_window);

	return app.exec();
}
