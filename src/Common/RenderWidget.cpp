#include <GL/glew.h>
#include "RenderWidget.hpp"
#include "../Common/FrameData.hpp"
#include <boost/algorithm/string/predicate.hpp>
#include <QFileDialog>
#include <boost/la/all.hpp>

using namespace boost::la;

RenderWidget::RenderWidget(FrameData& framedata) :
	framedata(framedata)
{
}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::init()
{
	GLint err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "glewInit() failed: " << glewGetErrorString(err)
				<< std::endl;
		exit(1);
	}
	std::cout << "Supports OpenGL " << glGetString(GL_VERSION) << "!"
			<< std::endl;
}

void RenderWidget::draw_light(int i, Light const& light) const
{
	if (i == 0 && !light.enabled)
	{
		glDisable(GL_LIGHTING);
		return;
	}
	else if (i == 0 && light.enabled)
	{
		glEnable(GL_LIGHTING);
	}

	if (!light.enabled)
	{
		glDisable(GL_LIGHT0 + i);
		return;
	}

	glEnable(GL_LIGHT0 + i);

	// colors
	glLightfv(GL_LIGHT0 + i, GL_AMBIENT, light.ambient);
	glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light.diffuse);
	glLightfv(GL_LIGHT0 + i, GL_SPECULAR, light.specular);

	// attenuation
	glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, light.const_att);
	glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, light.lin_att);
	glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, light.quad_att);

	if (light.is_spot)
	{
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, light.cut_off);
		glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, light.spot_direction);
		glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, light.exponent);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, Vec4(light.position | XYZ1));
	}
	else
	{
		glLightfv(GL_LIGHT0 + i, GL_POSITION, Vec4(light.position | XYZ0));
	}

	if (light.show_bulp)
		drawLight(GL_LIGHT0 + i);
}

void RenderWidget::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (std::size_t i = 0; i < framedata.num_lights(); ++i)
	{
		const FrameData& framedatac = framedata;
		draw_light(i, framedatac.light(i));
	}
	framedata.draw();
}

void RenderWidget::postDraw()
{
	startScreenCoordinatesSystem();
	framedata.drawLogo();
	stopScreenCoordinatesSystem();
	QGLViewer::postDraw();
}

void RenderWidget::resizeGL(int width, int height)
{
	framedata.resize(width, height);
	QGLViewer::resizeGL(width, height);
}

void RenderWidget::set_logo(bool checked)
{
	framedata.enable_logo(checked);
}

bool RenderWidget::logo_is_enabled() const
{
	return framedata.logo_is_enabled();
}

void RenderWidget::set_logo_path()
{
	QString tmp = QFileDialog::getOpenFileName(this,
			"Choose a logo texture to load", "../examples/Models/",
			"Textures (*.png *.jpg)");
	if (tmp != "")
	{
		framedata.set_logo_path(tmp.toStdString());
	}
}

QString RenderWidget::helpString() const
{
	return "<h2>S i m p l e V i e w e r</h2>"
		"Use the mouse to move the camera around the object. "
		"You can respectively revolve around, zoom and translate with the three mouse buttons. "
		"Left and middle buttons pressed together rotate around the camera view direction axis<br><br>"
		"Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. "
		"Simply press the function key again to restore it. Several keyFrames define a "
		"camera path. Paths are saved when you quit the application and restored at next start.<br><br>"
		"Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, "
		"<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. "
		"See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>"
		"Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). "
		"A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>"
		"A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. "
		"See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>"
		"Press <b>Escape</b> to exit the viewer.";
}
