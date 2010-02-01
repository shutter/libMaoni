/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <FL/Fl.H>
#include "Common/ConfigWindow.hpp"
#include <VMMView/detail/Algorithm.hpp>
#include "Common/FrameData.hpp"

#include <QApplication>
#include <boost/thread/thread.hpp>
#include "../Widgets/AlgorithmWidget.hpp"
#include "../Widgets/RenderWidget.hpp"
#include "../Widgets/RenderControlWidget.hpp"
#include "../Widgets/LightWidget.hpp"

void fltk_thread(FrameData& frame_data)
{
	ConfigWindow config_window(frame_data);
	Fl::run();
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	FrameData frame_data;

	RenderWidget viewer(frame_data);
	viewer.setWindowTitle("simpleViewer");
	viewer.show();

	RenderControlWidget control(frame_data);
	control.resize(240, 50);
	control.show();

	AlgorithmWidget algo_widget(frame_data);
	algo_widget.resize(240, 320);
	algo_widget.show();

	LightWidget light_widget(frame_data);
	light_widget.resize(240, 320);
	light_widget.show();

	boost::thread fltk(fltk_thread, boost::ref(frame_data));

	int ret = app.exec();

	fltk.join();

	return ret;
}
