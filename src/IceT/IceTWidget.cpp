#include "IceTWidget.hpp"
#include <cassert>

IceTWidget* IceTWidget::singleton = 0;

IceTWidget::IceTWidget(FrameData& frame_data) :
	RenderWidget(frame_data)
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
