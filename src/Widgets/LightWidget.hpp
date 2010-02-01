/*
 * LightWidget.hpp
 *
 *  Created on: Jan 30, 2010
 *      Author: stefan
 */

#ifndef LIGHTWIDGET_HPP_
#define LIGHTWIDGET_HPP_

#include <QWidget>
#include <QComboBox>
#include "Common/FrameData.hpp"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"

class LightWidget: public QWidget {
Q_OBJECT // Enable signals and slots
public:
	LightWidget(FrameData& frame_data, QWidget *parent = 0);

private slots:
	void test();
	void add_light();

private:
	FrameData& frame_data;
	QComboBox* light_chooser;
	QtTreePropertyBrowser* property_browser;

};

#endif /* LIGHTWIDGET_HPP_ */
