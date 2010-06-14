/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VMMVIEW_ALGORITHM_WIDGET_HPP
#define VMMVIEW_ALGORITHM_WIDGET_HPP

#include <QWidget>
#include <QComboBox>
#include <Maoni/RenderAlgorithm.hpp>
#include <qttreepropertybrowser.h>
#include <qtpropertymanager.h>
#include <filepathmanager.h>

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
	void property(const char* name, Path& value);
	void property(const char* name, Color& value);
	void property(const char* name, ShaderProgram& value)
	{
	}

private slots:
	void update_browser();
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
	QMap<QtProperty*, Path*> path_pointers;
	QMap<QtProperty*, Color*> color_pointers;

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
