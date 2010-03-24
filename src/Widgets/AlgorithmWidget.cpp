/*
 * RernderAlgoWidget.cpp
 *
 *  Created on: 07.12.2009
 *      Author: daniel
 */

#include "AlgorithmWidget.hpp"
#include <Maoni/detail/Algorithm.hpp>
#include <qteditorfactory.h>
#include <fileeditfactory.h>
#include <QVBoxLayout>
#include <iostream>

static QStringList AlgorithmNames()
{
	QStringList list;
	for (AlgorithmFactory* i = AlgorithmFactory::stack; i; i = i->next)
		list.append(i->name());
	return list;
}

AlgorithmWidget::AlgorithmWidget(RenderWidget& render_widget, QWidget *parent) :
	QWidget(parent), render_widget(render_widget)
{
	algo_chooser = new QComboBox;
	algo_chooser->addItems(AlgorithmNames());
	algo_chooser->show();

	property_browser = new QtTreePropertyBrowser;
	property_browser->show();

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(algo_chooser);
	layout->addWidget(property_browser);

	setLayout(layout);
	setWindowTitle("Algorithm");

	connect(algo_chooser, SIGNAL(currentIndexChanged(int)), this,
			SLOT(choose(int)));

	int_manager = new QtIntPropertyManager(this);
	bool_manager = new QtBoolPropertyManager(this);
	double_manager = new QtDoublePropertyManager(this);
	color_manager = new QtColorPropertyManager(this);
	filepath_manager = new FilePathManager(this);

	connect(int_manager, SIGNAL(valueChanged(QtProperty*, int)), this,
			SLOT(value_changed(QtProperty*, int)));
	connect(bool_manager, SIGNAL(valueChanged(QtProperty*, bool)), this,
			SLOT(value_changed(QtProperty*, bool)));
	connect(double_manager, SIGNAL(valueChanged(QtProperty*, double)), this,
			SLOT(value_changed(QtProperty*, double)));
	connect(color_manager, SIGNAL(valueChanged(QtProperty*, QColor)), this,
			SLOT(value_changed(QtProperty*, QColor)));
	connect(filepath_manager, SIGNAL(valueChanged(QtProperty*, QString)),this,
			SLOT(value_changed(QtProperty*, QString)));

	QtDoubleSpinBoxFactory* double_factory = new QtDoubleSpinBoxFactory(this);
	QtCheckBoxFactory* bool_factory = new QtCheckBoxFactory(this);
	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);
	QtColorEditorFactory* color_factory = new QtColorEditorFactory(this);
	FileEditFactory* filepath_factory = new FileEditFactory(this);

	property_browser->setFactoryForManager(int_manager, int_factory);
	property_browser->setFactoryForManager(bool_manager, bool_factory);
	property_browser->setFactoryForManager(double_manager, double_factory);
	property_browser->setFactoryForManager(color_manager, color_factory);
	property_browser->setFactoryForManager(
			color_manager->subIntPropertyManager(), int_factory);
	property_browser->setFactoryForManager(filepath_manager, filepath_factory);
}

void AlgorithmWidget::choose(int index)
{
	std::string name = algo_chooser->currentText().toStdString();
	render_widget.set_render_algorithm(name);

	int_setters.clear();
	bool_setters.clear();
	float_setters.clear();
	double_setters.clear();
	color_setters.clear();
	texture_setters.clear();

	property_browser->clear();
	config = AlgorithmFactory::create_config(name);
	config->config(*this);
}

void AlgorithmWidget::add_property(const char* name, int_setter func, int def)
{
	QtProperty* property = int_manager->addProperty(name);
	int_manager->setValue(property, def);
	property_browser->addProperty(property);
	int_setters[property] = func;
}

void AlgorithmWidget::add_property(const char* name, bool_setter func, bool def)
{
	QtProperty* property = bool_manager->addProperty(name);
	bool_manager->setValue(property, def);
	property_browser->addProperty(property);
	bool_setters[property] = func;
}

void AlgorithmWidget::add_property(const char* name, float_setter func,
		float def)
{
	QtProperty* property = double_manager->addProperty(name);
	double_manager->setValue(property, def);
	property_browser->addProperty(property);
	float_setters[property] = func;
}

void AlgorithmWidget::add_property(const char* name, double_setter func,
		double def)
{
	QtProperty* property = double_manager->addProperty(name);
	double_manager->setValue(property, def);
	property_browser->addProperty(property);
	double_setters[property] = func;
}

void AlgorithmWidget::add_property(const char* name, color_setter func,
		Color const& def)
{
	QtProperty* property = color_manager->addProperty(name);
	color_manager->setValue(property, QColor(def.red() * 255,
			def.green() * 255, def.blue() * 255, def.alpha() * 255));
	property_browser->addProperty(property);
	color_setters[property] = func;
}

void AlgorithmWidget::add_property(const char* name, texture_setter func,
		Texture const& def)
{
	QtProperty* property = filepath_manager->addProperty(name);
	filepath_manager->setValue(property, QString::fromStdString(def));
	filepath_manager->setFilter(property, "Image files (*.jpg *.png)");
	property_browser->addProperty(property);
	texture_setters[property] = func;
}
