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
	void update_browser();
private slots:
	void add_light();
	void remove_light();

	void choose(int i);

	void value_changed(QtProperty* property, const QString& value);
	void value_changed(QtProperty* property, int value);
	void value_changed(QtProperty* property, bool value);
	void value_changed(QtProperty* property, double value);
	void value_changed(QtProperty* property, const QColor& value);

	void update_combobox();

private:
	QColor colorOTB(Color const& one);
	Color colorBTO(QColor const& byte);

private:
	FrameData& frame_data;
	QComboBox* light_chooser;
	int light;
	QtTreePropertyBrowser* property_browser;

	QtStringPropertyManager* string_manager;
	QtIntPropertyManager* int_manager;
	QtBoolPropertyManager* bool_manager;
	QtDoublePropertyManager* double_manager;
	QtColorPropertyManager* color_manager;
    QtGroupPropertyManager* group_manager;

	QtProperty *name;
	QtProperty *is_on;
	QtProperty *show_bulp;
	QtProperty *pos_x;
	QtProperty *pos_y;
	QtProperty *pos_z;
	QtProperty *pos_v;
	QtProperty *light_position;
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
