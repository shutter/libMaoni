/*
 * main.cpp
 *
 *  Created on: Jan 18, 2010
 *      Author: daniel
 */

#include <GL/ice-t.h>
#include <GL/ice-t_mpi.h>

#include <iostream>

int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	IceTCommunicator communicator = icetCreateMPICommunicator(MPI_COMM_WORLD);
	IceTContext context = icetCreateContext(communicator);
	icetDestroyMPICommunicator(communicator);

	int rank, numprocs;

	icetGetIntegerv(ICET_RANK, &rank);
	icetGetIntegerv(ICET_NUM_PROCESSES, &numprocs);

	std::cout << "Process " << rank << " out of " << numprocs << std::endl;

	icetDestroyContext(context);
	MPI_Finalize();
}
