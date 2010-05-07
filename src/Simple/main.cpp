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
int maoni_main(int argc, char* argv[], //
		Algorithm* algorithm_stack, MeshLoader* mesh_loader_stack)
{
	QApplication app(argc, argv);
	Q_INIT_RESOURCE(Resources);

	QPixmap pixmap(":/Maoni/Splashscreen.png");
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
	splash.show();
	splash.showMessage("Loading Widgets...");

	FrameData framedata(algorithm_stack, mesh_loader_stack);

	MainWindow main_window(framedata, new RenderWidget(framedata));
	main_window.setWindowTitle("Maoni");

	QTimer::singleShot(1000, &main_window, SLOT(show()));
	QTimer::singleShot(1337, &splash, SLOT(close()));

	return app.exec();
}
