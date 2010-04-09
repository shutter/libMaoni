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

#include <iostream>

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	boost::mpi::environment env(argc, argv);
	QApplication app(argc, argv);

	std::cout << "t0" <<std::endl;

	IceTWidget* icet_widget = new IceTWidget(algorithm_factory_stack,
			mesh_loader_stack);

	std::cout << "t1 : "<< icet_widget->rank() <<  std::endl;

	QWidget* main_window;
	if (icet_widget->rank() == 0)
		main_window = new MainWindow(icet_widget);
	else
		main_window = icet_widget;

	std::cout << "t2" <<std::endl;

	main_window->setWindowTitle("Maoni Parallel Renderer");

	std::cout << "t3" <<std::endl;

	main_window->show();

	std::cout << "t4" <<std::endl;

	return app.exec();
}
