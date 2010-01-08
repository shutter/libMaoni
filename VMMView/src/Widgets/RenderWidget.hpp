#include <qglviewer-qt4/qglviewer.h>

#include "Common/FrameData.hpp"

class RenderWidget: public QGLViewer
{
Q_OBJECT

public:
	RenderWidget(FrameData& frame_data) :
		frame_data(frame_data)
	{
	}

private:
	void draw();

	QString helpString() const;

private:
	FrameData& frame_data;
};
