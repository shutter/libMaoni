/*
 * RernderAlgoWidget.hpp
 *
 *  Created on: 07.12.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_ALGORITHM_WIDGET_HPP
#define VMMVIEW_ALGORITHM_WIDGET_HPP

#include <QWidget>
#include <QComboBox>
#include <Maoni/Texture.hpp>
#include "Common/FrameData.hpp"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"
#include "filepathmanager.h"

class AlgorithmWidget: public QWidget, public AlgoConfigManager
{
Q_OBJECT

public:
	AlgorithmWidget(FrameData& frame_data, QWidget *parent = 0);

	void add_property(const char* name, int_setter func, int def);
	void add_property(const char* name, bool_setter func, bool def);
	void add_property(const char* name, float_setter func, float def);
	void add_property(const char* name, double_setter func, double def);
	void add_property(const char* name, color_setter func, Color const& def);
	void add_property(const char* name, texture_setter func, Texture const& def);

private slots:
	void choose(int index);

	void value_changed(QtProperty* property, int value)
	{
		if (int_setters.contains(property))
			int_setters[property](value);
	}

	void value_changed(QtProperty* property, bool value)
	{
		if (bool_setters.contains(property))
			bool_setters[property](value);
	}

	void value_changed(QtProperty* property, double value)
	{
		if (float_setters.contains(property))
			float_setters[property](value);
		if (double_setters.contains(property))
			double_setters[property](value);
	}

	void value_changed(QtProperty* property, const QColor& value)
	{
		if (color_setters.contains(property))
			color_setters[property](Color(value.redF(), value.greenF(),
					value.blueF(), value.alphaF()));
	}

	void value_changed(QtProperty* property, const QString& value)
	{
		if (texture_setters.contains(property))
			texture_setters[property](Texture(value.toStdString()));
	}

private:
	FrameData& frame_data;

	QMap<QtProperty*, int_setter> int_setters;
	QMap<QtProperty*, bool_setter> bool_setters;
	QMap<QtProperty*, float_setter> float_setters;
	QMap<QtProperty*, double_setter> double_setters;
	QMap<QtProperty*, color_setter> color_setters;
	QMap<QtProperty*, texture_setter> texture_setters;

	QComboBox* algo_chooser;
	QtTreePropertyBrowser* property_browser;

	QtIntPropertyManager* int_manager;
	QtBoolPropertyManager* bool_manager;
	QtDoublePropertyManager* double_manager;
	QtColorPropertyManager* color_manager;
	FilePathManager* filepath_manager;

	AlgoConfig::Ptr config;
};

#endif /* VMMVIEW_ALGORITHM_WIDGET_HPP */
