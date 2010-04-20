#include "IceTWidget.hpp"
#include <GL/ice-t_mpi.h>
#include <boost/assert.hpp>

IceTWidget* IceTWidget::singleton = 0;

IceTWidget::IceTWidget(FrameData& framedata) :
	RenderWidget(framedata)
{
	BOOST_ASSERT(!singleton && "Only one Instance of IceTWidget may exist");
	singleton = this;

	IceTCommunicator communicator = icetCreateMPICommunicator(MPI_COMM_WORLD);
	context = icetCreateContext(communicator);
	icetDestroyMPICommunicator(communicator);

	icetStrategy(ICET_STRATEGY_REDUCE);
	icetDrawFunc(static_draw);

	icetResetTiles();
	icetAddTile(0, 0, 500, 500, 0);
}

IceTWidget::~IceTWidget()
{
	icetDestroyContext(context);
}

void IceTWidget::static_draw()
{
	singleton->RenderWidget::draw();
}

void IceTWidget::paintGL()
{
	preDraw();
	icetDrawFrame();
	postDraw();

	// if(rank() != 0)
	// 	updateGL();
}
