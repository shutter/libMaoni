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
#include "RenderWidget.hpp"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"
#include "qvector3dpropertymanager.h"

class FrameData;

class LightWidget: public QWidget
{
Q_OBJECT // Enable signals and slots

public:
	LightWidget(FrameData& framedata, QWidget *parent = 0);

private slots:
	void update_browser();
	void choose(int i);

	void value_changed(QtProperty* property, bool value);
	void value_changed(QtProperty* property, double value);
	void value_changed(QtProperty* property, const QColor& value);
	void value_changed(QtProperty* property, const QVector3D& value);

	void update_combobox();

private:
	QColor colorOTB(Color const& one);
	Color colorBTO(QColor const& byte);

private:
	FrameData& framedata;
	QComboBox* light_chooser;
	int current_id;
	QtTreePropertyBrowser* property_browser;

	QtBoolPropertyManager* bool_manager;
	QtDoublePropertyManager* double_manager;
	QtColorPropertyManager* color_manager;
	QVector3DPropertyManager* vector3d_manager;
	QtGroupPropertyManager* group_manager;

	QtProperty *is_on;
	QtProperty *show_bulp;
	QtProperty *position;
	QtProperty *ambient;
	QtProperty *diffuse;
	QtProperty *specular;
	QtProperty *const_att;
	QtProperty *lin_att;
	QtProperty *quad_att;
	QtProperty *attenuation;
	QtProperty *is_spot;
	QtProperty *spot_dir_x;
	QtProperty *spot_dir_y;
	QtProperty *spot_dir_z;
	QtProperty *spot_direction;
	QtProperty *cut_off;
	QtProperty *exponent;
};

#endif /* LIGHTWIDGET_HPP_ */
