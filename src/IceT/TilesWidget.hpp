/*
 * TilesWidget.hpp
 *
 *  Created on: Mar 25, 2010
 *      Author: stefan
 */

#ifndef TILESWIDGET_HPP_
#define TILESWIDGET_HPP_

#include <QWidget>
#include <QComboBox>
#include "RenderWidget.hpp"
#include "qtpropertymanager.h"
#include "qttreepropertybrowser.h"
#include "../Common/Tile.hpp"

class TilesWidget: public QWidget
{
Q_OBJECT // Enable signals and slots
public:
	TilesWidget(RenderWidget& render_widget, QWidget *parent = 0);
	void update_browser();

private slots:
	void add_tile();
	void remove_tile();

	void choose(int i);

	void value_changed(QtProperty* property, const QString& value);
	void value_changed(QtProperty* property, int value);
	void value_changed(QtProperty* property, bool value);

	void update_combobox();

private:
	RenderWidget& render_widget;
	QComboBox* tile_chooser;
	int tile;
	QtTreePropertyBrowser* property_browser;

	std::vector<Tile> tmp_tiles_;

	QtStringPropertyManager* string_manager;
	QtIntPropertyManager* int_manager;
	QtBoolPropertyManager* bool_manager;
	QtGroupPropertyManager* group_manager;

	QtProperty *name;
	QtProperty *viewport;
	QtProperty *x;
	QtProperty *y;
	QtProperty *width;
	QtProperty *height;
	QtProperty *display_rank;
	QtProperty *is_active;
};

#endif /* TILESWIDGET_HPP_ */
