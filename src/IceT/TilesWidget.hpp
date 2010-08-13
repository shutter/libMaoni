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

#ifndef MAONI_ICET_TILESWIDGET_HPP
#define MAONI_ICET_TILESWIDGET_HPP

#include <QMap>
#include <QWidget>
#include <qtpropertymanager.h>
#include <qttreepropertybrowser.h>
#include <qvector3dpropertymanager.h>
#include "FrameData.hpp"
#include <Maoni/Vector.hpp>

class TilesWidget: public QWidget
{
Q_OBJECT

public:
	TilesWidget(FrameDataIceT& framedata);
	void update_browser();

private slots:
	void bool_changed(QtProperty* property, bool value);
	void enum_changed(QtProperty* property, int value);
	void point_changed(QtProperty* property, const QPoint& value);
	void vector_changed(QtProperty* property, const Vec3& value);

private:
	FrameDataIceT& framedata;
	QMap<QtProperty*, std::size_t> indices;

	QtTreePropertyBrowser* property_browser;

	QtBoolPropertyManager* bool_manager;
	QtEnumPropertyManager* enum_manager;
	QtPointPropertyManager* point_manager;
	QVector3DPropertyManager* vector3d_manager;
	QtGroupPropertyManager* group_manager;
};

#endif /* MAONI_ICET_TILESWIDGET_HPP */
