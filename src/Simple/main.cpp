/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */


#include <QApplication>
#include "Common/FrameData.hpp"
#include "../Widgets/MainWindow.hpp"

int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	QApplication app(argc, argv);

	FrameData frame_data(algorithm_factory_stack, mesh_loader_stack);

	MainWindow main_window(frame_data);
	main_window.setWindowTitle("Maoni");
	main_window.show();

	return app.exec();
}
