/*
 * main.cpp
 *
 *  Created on: Jan 18, 2010
 *      Author: Daniel Pfeifer
 */

#include <boost/mpi/environment.hpp>
#include <QApplication>
#include "IceTWidget.hpp"
#include "../Widgets/MainWindow.hpp"

int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	boost::mpi::environment env(argc, argv);
	QApplication app(argc, argv);

	IceTWidget* icet_widget = new IceTWidget(algorithm_factory_stack,
			mesh_loader_stack);

	QWidget* main_window;
	if (icet_widget->rank() == 0)
		main_window = new MainWindow(icet_widget);
	else
		main_window = icet_widget;

	main_window->setWindowTitle("Maoni Parallel Renderer");
	main_window->show();

	return app.exec();
}
