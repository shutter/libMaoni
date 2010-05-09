/*
 * main.cpp
 *
 *  Created on: Jan 18, 2010
 *      Author: Daniel Pfeifer
 */

#include <boost/mpi/environment.hpp>
#include <QApplication>

#include "IceTWidget.hpp"
#include "../Common/FrameData.hpp"
#include "../Widgets/MainWindow.hpp"

#ifdef _MSC_VER
__declspec(dllexport)
#endif
int maoni_main(int argc, char* argv[], //
		Algorithm* algorithm_stack, MeshLoader* mesh_loader_stack)
{
	boost::mpi::environment env(argc, argv);
	QApplication app(argc, argv);

	FrameData framedata(algorithm_stack, mesh_loader_stack);

	IceTWidget* icet_widget = new IceTWidget(framedata);

	QWidget* main_window;
	if (icet_widget->rank() == 0)
		main_window = new MainWindow(framedata, icet_widget);
	else
		main_window = icet_widget;

	main_window->setWindowTitle("Maoni using IceT Parallel Rendering");
	main_window->show();

	return app.exec();
}
