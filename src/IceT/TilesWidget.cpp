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

TilesWidget::TilesWidget(FrameDataIceT& framedata) :
	framedata(framedata)
{
	property_browser = new QtTreePropertyBrowser;
	property_browser->show();

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(property_browser);
	setLayout(layout);
	setWindowTitle("Tile Config");

	enum_manager = new QtEnumPropertyManager(this);
	point_manager = new QtPointPropertyManager(this);
	vector3d_manager = new QVector3DPropertyManager(this);
	group_manager = new QtGroupPropertyManager(this);

	connect(enum_manager, SIGNAL(valueChanged(QtProperty*, int)), //
			this, SLOT(enum_changed(QtProperty*, int)));
	connect(point_manager, SIGNAL(valueChanged(QtProperty*, QPoint const&)), //
			this, SLOT(point_changed(QtProperty*, QPoint const&)));
	connect(vector3d_manager, SIGNAL(valueChanged(QtProperty*, QVector3D const&)), //
			this, SLOT(vector_changed(QtProperty*, QVector3D const&)));


	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);
	QtEnumEditorFactory* enum_factory = new QtEnumEditorFactory(this);
	QtDoubleSpinBoxFactory* double_factory = new QtDoubleSpinBoxFactory(this);

	property_browser->setFactoryForManager(enum_manager, enum_factory);
	property_browser->setFactoryForManager(
			point_manager->subIntPropertyManager(), int_factory);
	property_browser->setFactoryForManager(
			vector3d_manager->subDoublePropertyManager(), double_factory);

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

	QString name = "Rank %1";
	for (std::size_t i = 0; i < framedata.tiles.size(); ++i)
	{
		Tile& tile = framedata.tiles[i];
		indices[property] = i;

		QtProperty* group = group_manager->addProperty(name.arg(i));
		QtProperty* point = point_manager->addProperty("Offset");
		QtProperty* size = point_manager->addProperty("Size");
		QtProperty* min = vector3d_manager->addProperty("Minimum");
		QtProperty* max = vector3d_manager->addProperty("Maximum");

		point_manager->setValue(point, QPoint(tile.x, tile.y));
		point_manager->setValue(size, QPoint(tile.sx, tile.sy));
		vector3d_manager->setValue(min, QVector3D(tile.min.data[0],
				tile.min.data[1], tile.min.data[2]));
		vector3d_manager->setValue(max, QVector3D(tile.max.data[0],
				tile.max.data[1], tile.max.data[2]));

		group->addSubProperty(point);
		group->addSubProperty(size);
		group->addSubProperty(min);
		group->addSubProperty(max);

		property_browser->addProperty(group);
	}
}

void TilesWidget::enum_changed(QtProperty* property, int value)
{
	framedata.setStrategy(value);
	//std::cout << "set strategy to " << value << std::endl;
}

void TilesWidget::point_changed(QtProperty* property, QPoint const& value)
{
	QString name = property->propertyName();
	Tile& tile = framedata.tiles[indices[property]];
	if (name == "Offset")
	{
		tile.x = value.x();
		tile.y = value.y();
	}
	else if (name == "Size")
	{
		tile.sx = value.x();
		tile.sy = value.y();
	}
	framedata.setTilesChanged();
}

void TilesWidget::vector_changed(QtProperty* property, QVector3D const& value)
{
	QString name = property->propertyName();
	Tile& tile = framedata.tiles[indices[property]];
	if (name == "Minimum")
	{
		tile.min = Vec3(value.x(), value.y(), value.z());
	}
	else if (name == "Maximum")
	{
		tile.max = Vec3(value.x(), value.y(), value.z());
	}
	framedata.setTilesChanged();
}
