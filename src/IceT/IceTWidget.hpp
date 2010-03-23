#include "../Widgets/RenderWidget.hpp"

#include <GL/ice-t.h>
#include <GL/ice-t_mpi.h>

class IceTWidget: public RenderWidget
{
Q_OBJECT

public:
	IceTWidget(FrameData& frame_data);
	~IceTWidget();

private:
	void draw();

private:
	IceTContext context;
	static IceTWidget* singleton;
};
