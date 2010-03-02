/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <Maoni/detail/Algorithm.hpp>
#include "Common/FrameData.hpp"

#include <QApplication>
#include <QDockWidget>

#include "../Widgets/AlgorithmWidget.hpp"
#include "../Widgets/RenderWidget.hpp"
#include "../Widgets/LightWidget.hpp"
#include "../Widgets/MainWindow.hpp"

int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	QApplication app(argc, argv);

	FrameData frame_data;

	MainWindow main_window(frame_data);

	QDockWidget *dock = new QDockWidget("Stefan's LightWidget", &main_window);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setWidget(new LightWidget(frame_data));
	main_window.addDockWidget(Qt::LeftDockWidgetArea, dock);

	dock = new QDockWidget("Daniels's AlgorithmWidget", &main_window);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setWidget(new AlgorithmWidget(frame_data));
	main_window.addDockWidget(Qt::RightDockWidgetArea, dock);

	main_window.setWindowTitle("Maoni");
	main_window.setCentralWidget(new RenderWidget(frame_data));
	main_window.show();

	return app.exec();
}
