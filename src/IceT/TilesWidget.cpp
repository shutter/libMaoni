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

#include "TilesWidget.hpp"
#include <qteditorfactory.h>
#include <QVBoxLayout>
#include <iostream>

TilesWidget::TilesWidget(QWidget *parent) :
	QWidget(parent), tiles(4)
{
	property_browser = new QtTreePropertyBrowser;
	property_browser->show();

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(property_browser);
	setLayout(layout);
	setWindowTitle("Tile Config");

	enum_manager = new QtEnumPropertyManager(this);
	rect_manager = new QtRectPropertyManager(this);
	QtIntPropertyManager* int_manager = new QtIntPropertyManager(this);

	connect(enum_manager, SIGNAL(valueChanged(QtProperty*, int)), //
		this, SLOT(enum_changed(QtProperty*, int)));
	connect(rect_manager, SIGNAL(valueChanged(QtProperty*, QRect const&)), //
		this, SLOT(rect_changed(QtProperty*, QRect const&)));

	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);
	QtEnumEditorFactory* enum_factory = new QtEnumEditorFactory(this);

	property_browser->setFactoryForManager(int_manager, int_factory);
	property_browser->setFactoryForManager(enum_manager, enum_factory);
	property_browser->setFactoryForManager(
		rect_manager->subIntPropertyManager(), int_factory);

	update_browser();
}

void TilesWidget::update_browser()
{
	property_browser->clear();
	indices.clear();

	QStringList strategies;
	strategies << "Direct" << "Serial" << "Split" << "Reduce" << "VTree";
	QtProperty* property = enum_manager->addProperty("Strategy");
	enum_manager->setEnumNames(property, strategies);
	enum_manager->setValue(property, 3);
	property_browser->addProperty(property);

	QString name = "Tile on Rank %1";
	for (std::size_t i = 0; i < tiles.size(); ++i)
	{
		Tile& tile = tiles[i];
		indices[property] = i;
		QtProperty* property = rect_manager->addProperty(name.arg(i));
		rect_manager->setValue(property, //
			QRect(tile.x, tile.y, tile.width, tile.height));
		property_browser->addProperty(property);
	}
}

void TilesWidget::enum_changed(QtProperty* property, int value)
{
	std::cout << "set strategy to " << value << std::endl;
}

void TilesWidget::rect_changed(QtProperty* property, QRect const& value)
{
	Tile& tile = tiles[indices[property]];
	tile.x = value.x();
	tile.y = value.y();
	tile.width = value.width();
	tile.height = value.height();
}
