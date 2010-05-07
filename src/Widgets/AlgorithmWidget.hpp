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
#include "RenderWidget.hpp"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"
#include "filepathmanager.h"

class FrameData;

class AlgorithmWidget: public QWidget, public AlgorithmConfig //, public AlgoConfigManager
{
Q_OBJECT

public:
	AlgorithmWidget(FrameData& framedata, QWidget *parent = 0);

//	void add_property(const char* name, int_setter func, int def);
//	void add_property(const char* name, bool_setter func, bool def);
//	void add_property(const char* name, float_setter func, float def);
//	void add_property(const char* name, double_setter func, double def);
//	void add_property(const char* name, color_setter func, Color const& def);
//	void add_property(const char* name, texture_setter func, Texture const& def);

	void property(const char* name, int& value);
	void property(const char* name, bool& value);
	void property(const char* name, float& value);
	void property(const char* name, double& value);
	void property(const char* name, Enum& value);
	void property(const char* name, Color& value);
	void property(const char* name, Texture& value);
	void property(const char* name, ShaderProgram& value)
	{
	}

private slots:
	void choose(int index);

	void value_changed(QtProperty* property, int value)
	{
		if (int_pointers.contains(property))
			*int_pointers[property] = value;
//		if (int_setters.contains(property))
//			int_setters[property](value);
	}

	void value_changed(QtProperty* property, bool value)
	{
		if (bool_pointers.contains(property))
			*bool_pointers[property] = value;
//		if (bool_setters.contains(property))
//			bool_setters[property](value);
	}

	void value_changed(QtProperty* property, double value)
	{
		if (float_pointers.contains(property))
			*float_pointers[property] = value;
		if (double_pointers.contains(property))
			*double_pointers[property] = value;
//		if (float_setters.contains(property))
//			float_setters[property](value);
//		if (double_setters.contains(property))
//			double_setters[property](value);
	}

	void value_changed(QtProperty* property, const QColor& value)
	{
		if (color_pointers.contains(property))
			*color_pointers[property] = Color(value.redF(), value.greenF(),
					value.blueF(), value.alphaF());
//		if (color_setters.contains(property))
//			color_setters[property](Color(value.redF(), value.greenF(),
//					value.blueF(), value.alphaF()));
	}

	void value_changed(QtProperty* property, const QString& value)
	{
		if (texture_pointers.contains(property))
			*texture_pointers[property] = Texture(value.toStdString());
//		if (texture_setters.contains(property))
//			texture_setters[property](Texture(value.toStdString()));
	}

private:
	FrameData& framedata;

	QMap<QtProperty*, int*> int_pointers;
	QMap<QtProperty*, bool*> bool_pointers;
	QMap<QtProperty*, float*> float_pointers;
	QMap<QtProperty*, double*> double_pointers;
	QMap<QtProperty*, Color*> color_pointers;
	QMap<QtProperty*, Texture*> texture_pointers;

//	QMap<QtProperty*, int_setter> int_setters;
//	QMap<QtProperty*, bool_setter> bool_setters;
//	QMap<QtProperty*, float_setter> float_setters;
//	QMap<QtProperty*, double_setter> double_setters;
//	QMap<QtProperty*, color_setter> color_setters;
//	QMap<QtProperty*, texture_setter> texture_setters;

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
