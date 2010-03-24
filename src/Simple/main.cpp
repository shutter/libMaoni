/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <QApplication>
#include "../Widgets/MainWindow.hpp"
#include "../Widgets/RenderWidget.hpp"

__declspec(dllexport) int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	QApplication app(argc, argv);

	MainWindow main_window(new RenderWidget(algorithm_factory_stack,
			mesh_loader_stack));
	main_window.setWindowTitle("Maoni");
	main_window.show();

	return app.exec();
}
