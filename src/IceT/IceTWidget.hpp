#include "../Widgets/RenderWidget.hpp"

#include <GL/ice-t.h>
#include <boost/mpi/communicator.hpp>

class IceTWidget: public RenderWidget, public boost::mpi::communicator
{
Q_OBJECT

public:
	IceTWidget(FrameData& framedata);

	~IceTWidget();

private:
	void draw();

private:
	IceTContext context;
	static IceTWidget* singleton;
	static void static_draw();
};
