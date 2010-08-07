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

#include "AnimationWidget.hpp"
#include <QVBoxLayout>
#include <qteditorfactory.h>
#include <iostream>
#include <limits.h>

#include <boost/la/all.hpp>
using namespace boost::la;

AnimationWidget::AnimationWidget(RenderWidget* renderwidget, QWidget *parent) :
	QWidget(parent), animate_v(false), period_v(40)
{
	renderwidget_ = renderwidget;

	QVBoxLayout* layout = new QVBoxLayout;

	property_browser = new QtTreePropertyBrowser;
	layout->addWidget(property_browser);

	setLayout(layout);
	setWindowTitle("Animation");

	bool_manager = new QtBoolPropertyManager(this);
	int_manager = new QtIntPropertyManager(this);

	animate = bool_manager->addProperty("animate");
	animate->setToolTip("Animate the render context with a constant frame rate");
	bool_manager->setValue(animate, animate_v);
	is_running = animate_v;

	period = int_manager->addProperty("period [ms]");
	period->setToolTip("Wait this delay after draw before drawing again");
	int_manager->setRange(period, 0, INT_MAX);
	int_manager->setValue(period, period_v);
	renderwidget_->setAnimationPeriod(period_v);

	QtCheckBoxFactory* bool_factory = new QtCheckBoxFactory(this);
	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);

	property_browser->setFactoryForManager(bool_manager, bool_factory);
	property_browser->setFactoryForManager(int_manager, int_factory);

	connect(bool_manager, SIGNAL(valueChanged(QtProperty*, bool)), this,
			SLOT(value_changed(QtProperty*, bool)));
	connect(int_manager, SIGNAL(valueChanged(QtProperty*, int)), this,
			SLOT(value_changed(QtProperty*, int)));


	property_browser->addProperty(animate);
	property_browser->addProperty(period);

	property_browser->show();
}

void AnimationWidget::value_changed(QtProperty* property, bool value)
{
	QString name = property->propertyName();
	if (name == "animate")
	{
		renderwidget_->toggleAnimation();
		is_running = value;
	}
}

void AnimationWidget::value_changed(QtProperty* property, int value)
{
	QString name = property->propertyName();
	if (name == "period [ms]")
	{
		renderwidget_->stopAnimation();
		renderwidget_->setAnimationPeriod(value);
		if(is_running) renderwidget_->startAnimation();
	}
}

