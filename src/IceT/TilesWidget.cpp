/*
 * TilesWidget.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: stefan
 */

#include "TilesWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <qteditorfactory.h>
#include <iostream>

TilesWidget::TilesWidget(RenderWidget& render_widget, QWidget *parent) :
	QWidget(parent), render_widget(render_widget), tile(0)
{
	tmp_tiles_ = render_widget.copy_tiles();

	QVBoxLayout* mainLayoutV = new QVBoxLayout;

	QHBoxLayout* layoutHlight = new QHBoxLayout;

	QGroupBox* horizontalGroupBoxLight = new QGroupBox();
	layoutHlight->setMargin(0);
	layoutHlight->setSpacing(-1);

	tile_chooser = new QComboBox;
	update_combobox();
	tile_chooser->show();
	layoutHlight->addWidget(tile_chooser);

	QPushButton* add_button = new QPushButton("+", this);
	add_button->setMaximumWidth(30);
	connect(add_button, SIGNAL(clicked()), this, SLOT(add_tile()));
	layoutHlight->addWidget(add_button);

	QPushButton* del_button = new QPushButton("-", this);
	del_button->setMaximumWidth(30);
	connect(del_button, SIGNAL(clicked()), this, SLOT(remove_tile()));
	layoutHlight->addWidget(del_button);

	horizontalGroupBoxLight->setLayout(layoutHlight);

	mainLayoutV->addWidget(horizontalGroupBoxLight);

	property_browser = new QtTreePropertyBrowser;
	mainLayoutV->addWidget(property_browser);

	setLayout(mainLayoutV);
	setWindowTitle("Tile Config");

	connect(tile_chooser, SIGNAL(activated(int)), this,
			SLOT(choose(int)));

	string_manager = new QtStringPropertyManager(this);
	int_manager = new QtIntPropertyManager(this);
	bool_manager = new QtBoolPropertyManager(this);
	group_manager = new QtGroupPropertyManager(this);

	name = string_manager->addProperty("name");
	name->setToolTip("A meaningful name for this tile");
	is_active = bool_manager->addProperty("activate");
	is_active->setToolTip("Activate or deactivate tile");

	viewport = group_manager->addProperty("viewport");
	viewport->setToolTip("Defines the tiles viewport in the logical global\n"
		"display much in the same way glViewport declares\n"
		"a region in a physical display.");
	x = int_manager->addProperty("x");
	y = int_manager->addProperty("y");
	width = int_manager->addProperty("width");
	height = int_manager->addProperty("height");

	viewport->addSubProperty(x);
	viewport->addSubProperty(y);
	viewport->addSubProperty(width);
	viewport->addSubProperty(height);

	display_rank = int_manager->addProperty("display rank");
	display_rank->setToolTip(
			"Identifies the rank of the process that will be\n"
				"displaying the given tile. Must have a valid rank\n"
				"(between 0 and ICET NUM PROCESSES − 1). Furthermore,\n"
				"no process may be displaying more than one tile.");

	QtLineEditFactory* string_factory = new QtLineEditFactory(this);
	QtCheckBoxFactory* bool_factory = new QtCheckBoxFactory(this);
	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);

	property_browser->setFactoryForManager(string_manager, string_factory);
	property_browser->setFactoryForManager(int_manager, int_factory);
	property_browser->setFactoryForManager(bool_manager, bool_factory);

	connect(int_manager, SIGNAL(valueChanged(QtProperty*, int)), this,
			SLOT(value_changed(QtProperty*, int)));
	connect(bool_manager, SIGNAL(valueChanged(QtProperty*, bool)), this,
			SLOT(value_changed(QtProperty*, bool)));
	connect(string_manager, SIGNAL(valueChanged(QtProperty*, QString)), this,
			SLOT(value_changed(QtProperty*, QString)));

	tile_chooser->setCurrentIndex(tile_chooser->count() - 1);
	choose(tmp_tiles_.size() - 1);
	property_browser->show();
}

void TilesWidget::add_tile()
{
	tmp_tiles_.push_back(Tile());
	update_combobox();
	tile_chooser->setCurrentIndex(tile_chooser->count() - 1);
	choose(tmp_tiles_.size() - 1);

}

void TilesWidget::remove_tile()
{
	tmp_tiles_.erase(tmp_tiles_.begin() + tile_chooser->currentIndex());
	update_combobox();
	tile_chooser->setCurrentIndex(tile_chooser->count() - 1);
	choose(tmp_tiles_.size() - 1);
}

void TilesWidget::update_combobox()
{
	QStringList list;
	tile_chooser->clear();
	for (unsigned int i = 0; i < tmp_tiles_.size(); i++)
		list.append(tmp_tiles_.at(i).getName().c_str());

	tile_chooser->addItems(list);
}

void TilesWidget::choose(int i)
{
	tile = i;

	property_browser->clear();

	string_manager->setValue(name, tmp_tiles_.at(i).getName().c_str());
	property_browser->addProperty(name);
	bool_manager->setValue(is_active, tmp_tiles_.at(i).getIs_active());
	property_browser->addProperty(is_active);

	if (tmp_tiles_.at(i).getIs_active())
	{
		x->setEnabled(true);
		y->setEnabled(true);
		width->setEnabled(true);
		height->setEnabled(true);
		display_rank->setEnabled(true);
	}
	else
	{
		x->setEnabled(false);
		y->setEnabled(false);
		width->setEnabled(false);
		height->setEnabled(false);
		display_rank->setEnabled(false);
	}

	int_manager->setValue(x, tmp_tiles_.at(i).getX());
	int_manager->setValue(y, tmp_tiles_.at(i).getY());
	int_manager->setValue(width, tmp_tiles_.at(i).getWidth());
	int_manager->setValue(height, tmp_tiles_.at(i).getHeight());
	int_manager->setValue(display_rank, tmp_tiles_.at(i).getDisplay_rank());

	property_browser->addProperty(viewport);

}

void TilesWidget::value_changed(QtProperty* property, int value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "x")
	{
		tmp_tiles_.at(tile).setX(value);
	}
	else if (name == "y")
	{
		tmp_tiles_.at(tile).setY(value);
	}
	else if (name == "width")
	{
		tmp_tiles_.at(tile).setWidth(value);
	}
	else if (name == "height")
	{
		tmp_tiles_.at(tile).setHeight(value);
	}
	else if (name == "display_rank")
	{
		tmp_tiles_.at(tile).setDisplay_rank(value);
	}
}

void TilesWidget::value_changed(QtProperty* property, bool value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "activate")
	{
		tmp_tiles_.at(tile).setIs_active(value);
		choose(tile_chooser->currentIndex());
	}
}

void TilesWidget::value_changed(QtProperty* property, const QString& value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "name")
	{
		tmp_tiles_.at(tile).setName(value.toStdString());
	}
}

void TilesWidget::update_browser()
{
	update_combobox();
	choose(0);
}

