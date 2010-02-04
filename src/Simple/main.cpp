/*
 * main.cpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#include <Maoni/detail/Algorithm.hpp>
#include "Common/FrameData.hpp"

#include <QApplication>
#include "../Widgets/AlgorithmWidget.hpp"
#include "../Widgets/RenderWidget.hpp"
#include "../Widgets/RenderControlWidget.hpp"
#include "../Widgets/LightWidget.hpp"

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

	return app.exec();
}
