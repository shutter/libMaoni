/*
 * RenderControlWidget.hpp
 *
 *  Created on: Dec 5, 2009
 *      Author: stefan
 */

#ifndef RENDERCONTROLWIDGET_HPP_
#define RENDERCONTROLWIDGET_HPP_

#include <QWidget>
#include "../Common/FrameData.hpp"

class RenderControlWidget: public QWidget
{
Q_OBJECT

public:
	RenderControlWidget(FrameData& frame_data, QWidget *parent = 0);

private slots:
	void load_model();

	void show_logo(int state);

private:
	FrameData& frame_data;
};

#endif /* RENDERCONTROLWIDGET_HPP_ */
