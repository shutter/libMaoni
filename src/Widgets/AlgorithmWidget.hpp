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

class AlgorithmWidget: public QWidget, public AlgorithmConfig
{
Q_OBJECT

public:
	AlgorithmWidget(FrameData& framedata, QWidget *parent = 0);

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

	void value_changed(QtProperty* property, int value);
	void value_changed(QtProperty* property, bool value);
	void value_changed(QtProperty* property, double value);
	void value_changed(QtProperty* property, const QColor& value);
	void value_changed(QtProperty* property, const QString& value);

private:
	FrameData& framedata;

	QMap<QtProperty*, int*> int_pointers;
	QMap<QtProperty*, bool*> bool_pointers;
	QMap<QtProperty*, float*> float_pointers;
	QMap<QtProperty*, double*> double_pointers;
	QMap<QtProperty*, Enum*> enum_pointers;
	QMap<QtProperty*, Color*> color_pointers;
	QMap<QtProperty*, Texture*> texture_pointers;

	QComboBox* algo_chooser;
	QtTreePropertyBrowser* property_browser;

	QtIntPropertyManager* int_manager;
	QtBoolPropertyManager* bool_manager;
	QtDoublePropertyManager* double_manager;
	QtEnumPropertyManager* enum_manager;
	QtColorPropertyManager* color_manager;
	FilePathManager* filepath_manager;
};

#endif /* VMMVIEW_ALGORITHM_WIDGET_HPP */
