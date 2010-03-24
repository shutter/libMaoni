#include "IceTWidget.hpp"
#include <cassert>

IceTWidget* IceTWidget::singleton = 0;

IceTWidget::IceTWidget(AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack) :
	RenderWidget(algorithm_factory_stack, mesh_loader_stack)
{
	assert(!singleton && "Only one Instance of IceTWidget may exist");
	singleton = this;

	IceTCommunicator communicator = icetCreateMPICommunicator(MPI_COMM_WORLD);
	context = icetCreateContext(communicator);
	icetDestroyMPICommunicator(communicator);
}

IceTWidget::~IceTWidget()
{
	icetDestroyContext(context);
}

void IceTWidget::draw()
{
	singleton->RenderWidget::draw();
}
