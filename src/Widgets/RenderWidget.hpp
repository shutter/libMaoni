#ifndef RENDER_WIDGET_HPP
#define RENDER_WIDGET_HPP

#include <qglviewer.h>
#include <boost/noncopyable.hpp>

#include "../Common/Light.hpp"
//#include "../Common/Tile.hpp"
#include <Maoni/Model.hpp>
#include <Maoni/RenderAlgorithm.hpp>
#include <Maoni/detail/MeshLoader.hpp>

class FrameData;

class RenderWidget: public QGLViewer, private boost::noncopyable
{
Q_OBJECT

public:
	RenderWidget(FrameData& framedata);

	virtual ~RenderWidget();

	bool logo_is_enabled() const;

private slots:
	void set_logo_path();
	void set_logo(bool checked);

private:
	void init();
	QString helpString() const;

	void draw_light(int i, Light const& light) const;

protected:
	void resizeGL(int width, int height);

protected:
	void draw();

protected:
	FrameData& framedata;
};

#endif /* RENDER_WIDGET_HPP */
