#include <qglviewer.h>

#include "Common/FrameData.hpp"

class RenderWidget: public QGLViewer
{
Q_OBJECT

public:
	RenderWidget(FrameData& frame_data) :
		frame_data(frame_data)
	{
	}

protected:
	void init();
	void draw();

	QString helpString() const;

private:
	FrameData& frame_data;
};
