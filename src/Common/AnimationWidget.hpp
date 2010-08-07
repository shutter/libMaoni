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

#ifndef ANIMATIONWIDGET_HPP_
#define ANIMATIONWIDGET_HPP_


#include <QWidget>
#include "RenderWidget.hpp"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"

class RenderWidget;

class AnimationWidget: public QWidget
{
Q_OBJECT // Enable signals and slots

public:
	AnimationWidget(RenderWidget* renderwidget, QWidget *parent = 0);

private slots:
	void value_changed(QtProperty* property, bool value);
	void value_changed(QtProperty* property, int value);

private:
	RenderWidget* renderwidget_;
	QtTreePropertyBrowser* property_browser;

	QtBoolPropertyManager* bool_manager;
	QtIntPropertyManager* int_manager;

	QtProperty *animate;
	QtProperty *period;

	bool animate_v;
	int period_v;
	bool is_running;

};


#endif /* ANIMATIONWIDGET_HPP_ */
