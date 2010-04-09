/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <QApplication>
#include <QSplashScreen>
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

    QPixmap pixmap("libmaoni_sscr.png");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();

    splash.showMessage("Loading Widgets...");
	MainWindow main_window(new RenderWidget(algorithm_factory_stack,
			mesh_loader_stack));
	main_window.setWindowTitle("Maoni");
	main_window.show();

	QTimer::singleShot(3000, &splash, SLOT(close()));
    //splash.finish(&main_window);

	return app.exec();
}
