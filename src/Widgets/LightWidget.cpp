/*
 * LightWidget.cpp
 *
 *  Created on: Jan 30, 2010
 *      Author: stefan
 */

#include "LightWidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <qteditorfactory.h>
#include <iostream>

LightWidget::LightWidget(FrameData& frame_data, QWidget *parent) :
	QWidget(parent), frame_data(frame_data), light(frame_data.lights()[0]) {
	QVBoxLayout* mainLayoutV = new QVBoxLayout;

	QHBoxLayout* layoutH = new QHBoxLayout;
	QGroupBox* horizontalGroupBox = new QGroupBox();

	QPushButton* add_button = new QPushButton("add", this);
	connect(add_button, SIGNAL(clicked()), this, SLOT(add_light()));
	layoutH->addWidget(add_button);

	QPushButton* del_button = new QPushButton("del", this);
	connect(del_button, SIGNAL(clicked()), this, SLOT(test()));
	layoutH->addWidget(del_button);

	QPushButton* load_button = new QPushButton("load", this);
	connect(load_button, SIGNAL(clicked()), this, SLOT(test()));
	layoutH->addWidget(load_button);

	horizontalGroupBox->setLayout(layoutH);

	light_chooser = new QComboBox;
	light_chooser->addItems(getLightNames());
	light_chooser->show();
	mainLayoutV->addWidget(light_chooser);

	mainLayoutV->addWidget(horizontalGroupBox);

	property_browser = new QtTreePropertyBrowser;
	mainLayoutV->addWidget(property_browser);

	setLayout(mainLayoutV);
	setWindowTitle("Light Control");

	connect(light_chooser, SIGNAL(currentIndexChanged(int)), this,
			SLOT(choose(int)));

	string_manager = new QtStringPropertyManager(this);
	int_manager = new QtIntPropertyManager(this);
	bool_manager = new QtBoolPropertyManager(this);
	double_manager = new QtDoublePropertyManager(this);
	color_manager = new QtColorPropertyManager(this);
	group_manager = new QtGroupPropertyManager(this);

	name = string_manager->addProperty("name");
	name->setToolTip("A meaningful name for this light source");
	is_on = bool_manager->addProperty("activate");
	is_on->setToolTip("Turn light on and off");
	show_bulp = bool_manager->addProperty("show bulp");
	show_bulp->setToolTip("Draw the light source");
	pos_x = double_manager->addProperty("x");
	pos_y = double_manager->addProperty("y");
	pos_z = double_manager->addProperty("z");
	pos_v = double_manager->addProperty("v");
	light_position = group_manager->addProperty("light position");
	light_position->addSubProperty(pos_x);
	light_position->addSubProperty(pos_y);
	light_position->addSubProperty(pos_z);
	light_position->addSubProperty(pos_v);
	ambient = color_manager->addProperty("ambient");
	ambient->setToolTip(
			"Bounced light which is assumed to be so scattered that there is no way to tell its original direction, but it disappears if this light source is turned off.");
	diffuse = color_manager->addProperty("diffuse");
	diffuse->setToolTip(
			"Comes from one direction, so it's brighter if it comes squarely down on a surface than if it barely glances off the surface. Once it hits a surface, however, it's scattered equally in all directions, so it appears equally bright, no matter where the eye is located.");
	specular = color_manager->addProperty("specular");
	specular->setToolTip(
			"Comes from a particular direction, and tends to bounce off the surface in a preferred direction. You can think of specularity as the shininess of a certain material.");
	const_att = double_manager->addProperty("constant attenuation");
	lin_att = double_manager->addProperty("linear attenuation");
	quad_att = double_manager->addProperty("quadratic attenuation");
	attenuation = group_manager->addProperty("attenuation");
	attenuation->setToolTip(
			"For positional light, the intensity decreases as distance from the light increases. OpenGL attenuates a light source by multiplying the contribution of that source by an attenuation factor.");
	attenuation->addSubProperty(const_att);
	attenuation->addSubProperty(lin_att);
	attenuation->addSubProperty(quad_att);
	is_spot = bool_manager->addProperty("spot light");
	is_spot->setToolTip(
			"Make positional light source act as a spotlight by restricting the shape of the light it emits to a cone.");
	spot_dir_x = double_manager->addProperty("x");
	spot_dir_y = double_manager->addProperty("y");
	spot_dir_z = double_manager->addProperty("z");
	spot_direction = group_manager->addProperty("spot direction");
	spot_direction->addSubProperty(spot_dir_x);
	spot_direction->addSubProperty(spot_dir_y);
	spot_direction->addSubProperty(spot_dir_z);
	cut_off = double_manager->addProperty("cut off angle");
	cut_off->setToolTip(
			"Specifies the angle between the axis of the cone and a ray along the edge of the cone. The angle of the cone at the apex is then twice this value.");
	double_manager->setRange(cut_off, 0.0, 90.0);
	exponent = double_manager->addProperty("exponent");

	QtDoubleSpinBoxFactory* double_factory = new QtDoubleSpinBoxFactory(this);
	QtCheckBoxFactory* bool_factory = new QtCheckBoxFactory(this);
	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);
	QtColorEditorFactory* color_factory = new QtColorEditorFactory(this);

	property_browser->setFactoryForManager(int_manager, int_factory);
	property_browser->setFactoryForManager(bool_manager, bool_factory);
	property_browser->setFactoryForManager(double_manager, double_factory);
	property_browser->setFactoryForManager(color_manager, color_factory);
	property_browser->setFactoryForManager(
			color_manager->subIntPropertyManager(), int_factory);

	connect(int_manager, SIGNAL(valueChanged(QtProperty*, int)), this,
			SLOT(value_changed(QtProperty*, int)));
	connect(bool_manager, SIGNAL(valueChanged(QtProperty*, bool)), this,
			SLOT(value_changed(QtProperty*, bool)));
	connect(double_manager, SIGNAL(valueChanged(QtProperty*, double)), this,
			SLOT(value_changed(QtProperty*, double)));
	connect(color_manager, SIGNAL(valueChanged(QtProperty*, QColor)), this,
			SLOT(value_changed(QtProperty*, QColor)));
	connect(string_manager, SIGNAL(valueChanged(QtProperty*, std::string)), this,
			SLOT(value_changed(QtProperty*, QColor)));

	light_chooser->setCurrentIndex(frame_data.lights().size() - 1);
	choose(frame_data.lights().size() - 1);
	property_browser->show();

}

void LightWidget::add_light() {
	std::cout << "add light" << std::endl;

	if (frame_data.lights().size() >= frame_data.max_number_of_lights) {
		QMessageBox::warning(this, "Error", "Maximal Number of Lights reached!");
	} else {
		frame_data.lights().push_back(Light());
		light_chooser->addItem(frame_data.lights()[frame_data.lights().size()-1].name.c_str());
		light_chooser->setCurrentIndex(frame_data.lights().size()-1);
		//choose(frame_data.lights().size() - 1);

	}
}

void LightWidget::choose(int i) {
	light = frame_data.lights()[i];
	property_browser->clear();

	string_manager->setValue(name, light.name.c_str());
	property_browser->addProperty(name);
	bool_manager->setValue(is_on, light.is_on);
	property_browser->addProperty(is_on);

	if (light.is_on) {
		show_bulp->setEnabled(true);
		light_position->setEnabled(true);
		ambient->setEnabled(true);
		diffuse->setEnabled(true);
		specular->setEnabled(true);
		attenuation->setEnabled(true);
		is_spot->setEnabled(true);
		spot_direction->setEnabled(true);
		cut_off->setEnabled(true);
		exponent->setEnabled(true);
	} else {
		show_bulp->setEnabled(false);
		light_position->setEnabled(false);
		ambient->setEnabled(false);
		diffuse->setEnabled(false);
		specular->setEnabled(false);
		attenuation->setEnabled(false);
		is_spot->setEnabled(false);
		spot_direction->setEnabled(false);
		cut_off->setEnabled(false);
		exponent->setEnabled(false);
	}
	bool_manager->setValue(show_bulp, light.show_bulp);
	property_browser->addProperty(show_bulp);
	double_manager->setValue(pos_x, light.position[0]);
	double_manager->setValue(pos_y, light.position[1]);
	double_manager->setValue(pos_z, light.position[2]);
	double_manager->setValue(pos_v, light.position[3]);
	property_browser->addProperty(light_position);
	color_manager->setValue(ambient, colorOTB(light.ambient));
	property_browser->addProperty(ambient);
	color_manager->setValue(diffuse, colorOTB(light.diffuse));
	property_browser->addProperty(diffuse);
	color_manager->setValue(specular, colorOTB(light.specular));
	property_browser->addProperty(specular);
	double_manager->setValue(const_att, light.const_att);
	double_manager->setValue(lin_att, light.lin_att);
	double_manager->setValue(quad_att, light.quad_att);
	property_browser->addProperty(attenuation);

	if (!light.is_light0) {
		bool_manager->setValue(is_spot, light.is_spot);
		property_browser->addProperty(is_spot);
		double_manager->setValue(spot_dir_x, light.spot_direction[0]);
		double_manager->setValue(spot_dir_y, light.spot_direction[1]);
		double_manager->setValue(spot_dir_z, light.spot_direction[2]);
		property_browser->addProperty(spot_direction);
		double_manager->setValue(cut_off, light.cut_off);
		property_browser->addProperty(cut_off);
		double_manager->setValue(exponent, light.exponent);
		property_browser->addProperty(exponent);
	}

	//std::cout << "light blue: " << light.ambient.array[2] << "picker blue: " << color_manager->value(ambient).blue() << std::endl;

}

QStringList LightWidget::getLightNames() {
	QStringList list;
	for (unsigned int i = 0; i < frame_data.lights().size(); i++)
		list.append(frame_data.lights()[0].name.c_str());
	return list;
}

QColor LightWidget::colorOTB(Vector4 one) {
	return QColor(one.array[0] * 255, one.array[1] * 255, one.array[2] * 255,
			one.array[3] * 255);
}

void LightWidget::colorBTO(QColor byte, Vector4 one) {
	one.array[0] = byte.red() / 255.0;
	one.array[1] = byte.green() / 255.0;
	one.array[2] = byte.blue() / 255.0;
	one.array[3] = byte.alpha() / 255.0;
}

void LightWidget::value_changed(QtProperty* property, int value) {
	std::string name = property->propertyName().toStdString();
}

void LightWidget::value_changed(QtProperty* property, bool value) {
	std::string name = property->propertyName().toStdString();
	if (name == "is_on") {
		light.is_on = value;
	} else if (name == "show_bulp") {
		light.show_bulp = value;
	} else if (name == "is_spot") {
		light.is_spot = value;
	}
}

void LightWidget::value_changed(QtProperty* property, double value) {
	std::string name = property->propertyName().toStdString();
	if (name == "pos_x") {
		light.position[0] = value;
	} else if (name == "pos_y") {
		light.position[1] = value;
	} else if (name == "pos_z") {
		light.position[2] = value;
	} else if (name == "pos_v") {
		light.position[3] = value;
	} else if (name == "const_att") {
		light.const_att = value;
	} else if (name == "lin_att") {
		light.lin_att = value;
	} else if (name == "quad_att") {
		light.quad_att = value;
	} else if (name == "spot_dir_x") {
		light.spot_direction[0] = value;
	} else if (name == "spot_dir_y") {
		light.spot_direction[1] = value;
	} else if (name == "spot_dir_z") {
		light.spot_direction[2] = value;
	} else if (name == "cut_off") {
		light.cut_off = value;
	} else if (name == "exponent") {
		light.exponent = value;
	}
}

void LightWidget::value_changed(QtProperty* property, const QColor& value) {
	std::string name = property->propertyName().toStdString();
	if (name == "ambient") {
		light.ambient[0] = value.red();
		light.ambient[1] = value.green();
		light.ambient[2] = value.blue();
		light.ambient[3] = value.alpha();
	} else if (name == "diffuse") {
		light.diffuse[0] = value.red();
		light.diffuse[1] = value.green();
		light.diffuse[2] = value.blue();
		light.diffuse[3] = value.alpha();
	} else if (name == "specular") {
		light.specular[0] = value.red();
		light.specular[1] = value.green();
		light.specular[2] = value.blue();
		light.specular[3] = value.alpha();
	}
}

void LightWidget::value_changed(QtProperty* property, const QString& value) {
	std::string name = property->propertyName().toStdString();
	if (name == "name") {
		light.name = value.toStdString();
	}
}

void LightWidget::test() {
	std::cout << "test" << std::endl;
}
