/*
 * main.cpp
 *
 *  Created on: Jan 18, 2010
 *      Author: Daniel Pfeifer
 */

#include <mpi.h>
#include <GL/ice-t.h>
#include <QApplication>
#include "../Widgets/MainWindow.hpp"
#include "IceTWidget.hpp"
#include <iostream>

struct mpi_raii
{
	mpi_raii(int *argc, char ***argv)
	{
		MPI_Init(argc, argv);
	}

	~mpi_raii()
	{
		MPI_Finalize();
	}
};

int maoni_main(int argc, char* argv[],
		AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack)
{
	mpi_raii mpi(&argc, &argv);
	QApplication app(argc, argv);

	IceTWidget* icet_widget = new IceTWidget(algorithm_factory_stack,
			mesh_loader_stack);

	int rank, numprocs;
	icetGetIntegerv(ICET_RANK, &rank);
	icetGetIntegerv(ICET_NUM_PROCESSES, &numprocs);

	std::cout << "Process " << rank << " out of " << numprocs << std::endl;

	QWidget* main_window;
	if (rank == 0)
		main_window = new MainWindow(icet_widget);
	else
		main_window = icet_widget;

	main_window->setWindowTitle("Maoni Parallel Renderer");
	main_window->show();

	return app.exec();
}
