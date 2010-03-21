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
	QWidget(parent), frame_data(frame_data), light(0)
{
	QVBoxLayout* mainLayoutV = new QVBoxLayout;

	QHBoxLayout* layoutHfile = new QHBoxLayout;
	QHBoxLayout* layoutHlight = new QHBoxLayout;

	QGroupBox* horizontalGroupBoxFile = new QGroupBox();
	QGroupBox* horizontalGroupBoxLight = new QGroupBox();

	QPushButton* add_button = new QPushButton("add", this);
	connect(add_button, SIGNAL(clicked()), this, SLOT(add_light()));
	layoutHlight->addWidget(add_button);

	QPushButton* del_button = new QPushButton("del", this);
	connect(del_button, SIGNAL(clicked()), this, SLOT(test()));
	layoutHlight->addWidget(del_button);

	QPushButton* load_button = new QPushButton("load", this);
	connect(load_button, SIGNAL(clicked()), this, SLOT(test()));
	layoutHfile->addWidget(load_button);

	QPushButton* save_button = new QPushButton("save", this);
	connect(load_button, SIGNAL(clicked()), this, SLOT(test()));
	layoutHfile->addWidget(save_button);

	horizontalGroupBoxFile->setLayout(layoutHfile);
	horizontalGroupBoxLight->setLayout(layoutHlight);

	mainLayoutV->addWidget(horizontalGroupBoxFile);

	light_chooser = new QComboBox;
	update_combobox();
	light_chooser->show();
	mainLayoutV->addWidget(light_chooser);

	mainLayoutV->addWidget(horizontalGroupBoxLight);

	property_browser = new QtTreePropertyBrowser;
	mainLayoutV->addWidget(property_browser);

	setLayout(mainLayoutV);
	setWindowTitle("Light Control");

	connect(light_chooser, SIGNAL(activated(int)), this,
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
	pos_x = double_manager->addProperty("pos x");
	pos_y = double_manager->addProperty("pos y");
	pos_z = double_manager->addProperty("pos z");
	pos_v = double_manager->addProperty("pos v");
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
	spot_dir_x = double_manager->addProperty("spot x");
	spot_dir_y = double_manager->addProperty("spot y");
	spot_dir_z = double_manager->addProperty("spot z");
	spot_direction = group_manager->addProperty("spot direction");
	spot_direction->addSubProperty(spot_dir_x);
	spot_direction->addSubProperty(spot_dir_y);
	spot_direction->addSubProperty(spot_dir_z);
	cut_off = double_manager->addProperty("cut off angle");
	cut_off->setToolTip(
			"Specifies the angle between the axis of the cone and a ray along the edge of the cone. The angle of the cone at the apex is then twice this value.");
	double_manager->setRange(cut_off, 0.0, 90.0);
	exponent = double_manager->addProperty("exponent");

	QtLineEditFactory* string_factory = new QtLineEditFactory(this);
	QtDoubleSpinBoxFactory* double_factory = new QtDoubleSpinBoxFactory(this);
	QtCheckBoxFactory* bool_factory = new QtCheckBoxFactory(this);
	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);
	QtColorEditorFactory* color_factory = new QtColorEditorFactory(this);

	property_browser->setFactoryForManager(string_manager, string_factory);
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
	connect(string_manager, SIGNAL(valueChanged(QtProperty*, QString)), this,
			SLOT(value_changed(QtProperty*, QString)));

	light_chooser->setCurrentIndex(light_chooser->count() - 1);
	choose(frame_data.get_lights_size() - 1);
	property_browser->show();

}

void LightWidget::add_light()
{
	if (frame_data.add_light())
	{
		update_combobox();
		light_chooser->setCurrentIndex(light_chooser->count() - 1);
		choose(frame_data.get_lights_size() - 1);
	}
	else
	{
		QMessageBox::warning(this, "Error", "Maximal Number of Lights reached!");
	}
}

void LightWidget::update_combobox()
{
	QStringList list;
	light_chooser->clear();
	for (unsigned int i = 0; i < frame_data.get_lights_size(); i++)
		list.append(frame_data.get_light(i).getName().c_str());

	light_chooser->addItems(list);
}

void LightWidget::choose(int i)
{
	light = i;

	property_browser->clear();

	string_manager->setValue(name, frame_data.get_light(i).getName().c_str());
	property_browser->addProperty(name);
	bool_manager->setValue(is_on, frame_data.get_light(i).getIs_on());
	property_browser->addProperty(is_on);

	if (frame_data.get_light(i).getIs_on())
	{
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
	}
	else
	{
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
	bool_manager->setValue(show_bulp, frame_data.get_light(i).getShow_bulp());
	property_browser->addProperty(show_bulp);
	double_manager->setValue(pos_x, frame_data.get_light(i).getPosition()[0]);
	double_manager->setValue(pos_y, frame_data.get_light(i).getPosition()[1]);
	double_manager->setValue(pos_z, frame_data.get_light(i).getPosition()[2]);
	double_manager->setValue(pos_v, frame_data.get_light(i).getPosition()[3]);
	property_browser->addProperty(light_position);
	color_manager->setValue(ambient, colorOTB(
			frame_data.get_light(i).getAmbient()));
	property_browser->addProperty(ambient);
	color_manager->setValue(diffuse, colorOTB(
			frame_data.get_light(i).getDiffuse()));
	property_browser->addProperty(diffuse);
	color_manager->setValue(specular, colorOTB(
			frame_data.get_light(i).getSpecular()));
	property_browser->addProperty(specular);
	double_manager->setValue(const_att, frame_data.get_light(i).getConst_att());
	double_manager->setValue(lin_att, frame_data.get_light(i).getLin_att());
	double_manager->setValue(quad_att, frame_data.get_light(i).getQuad_att());
	property_browser->addProperty(attenuation);

	if (!frame_data.get_light(i).getIs_light0())
	{
		bool_manager->setValue(is_spot, frame_data.get_light(i).getIs_spot());
		property_browser->addProperty(is_spot);
		double_manager->setValue(spot_dir_x,
				frame_data.get_light(i).getSpot_direction()[0]);
		double_manager->setValue(spot_dir_y,
				frame_data.get_light(i).getSpot_direction()[1]);
		double_manager->setValue(spot_dir_z,
				frame_data.get_light(i).getSpot_direction()[2]);
		property_browser->addProperty(spot_direction);
		double_manager->setValue(cut_off, frame_data.get_light(i).getCut_off());
		property_browser->addProperty(cut_off);
		double_manager->setValue(exponent,
				frame_data.get_light(i).getExponent());
		property_browser->addProperty(exponent);
	}
}

QColor LightWidget::colorOTB(Color const& one)
{
	return QColor(one.red() * 255.0, one.green() * 255.0, one.blue() * 255.0,
			one.alpha() * 255.0);
}

Color LightWidget::colorBTO(QColor const& byte)
{
	return Color(byte.red() / 255.0, byte.green() / 255.0, byte.blue()
			/ 255.0, byte.alpha() / 255.0);
}

void LightWidget::value_changed(QtProperty* property, int value)
{
	std::string name = property->propertyName().toStdString();
}

void LightWidget::value_changed(QtProperty* property, bool value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "activate")
	{
		frame_data.get_light(light).setIs_on(value);
	}
	else if (name == "show bulp")
	{
		frame_data.get_light(light).setShow_bulp(value);
	}
	else if (name == "spot light")
	{
		frame_data.get_light(light).setIs_spot(value);
	}
}

void LightWidget::value_changed(QtProperty* property, double value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "pos x" || name == "pos y" || name == "pos z" || name
			== "pos v")
	{
		frame_data.get_light(light).setPosition(Vector4(double_manager->value(
				pos_x), double_manager->value(pos_y), double_manager->value(
				pos_z), double_manager->value(pos_v)));
		frame_data.get_light(light).recalcLightBox(0.05);

	}
	else if (name == "constant attenuation")
	{
		frame_data.get_light(light).setConst_att(value);
	}
	else if (name == "linear attenuation")
	{
		frame_data.get_light(light).setLin_att(value);
	}
	else if (name == "quadratic attenuation")
	{
		frame_data.get_light(light).setQuad_att(value);
	}
	else if (name == "spot x" || name == "spot y" || name == "spot z")
	{
		frame_data.get_light(light).setSpot_direction(Vector3(
				double_manager->value(spot_dir_x), double_manager->value(
						spot_dir_y), double_manager->value(spot_dir_z)));
		frame_data.get_light(light).recalcLightBox(0.05);
	}
	else if (name == "cut off angle")
	{
		frame_data.get_light(light).setCut_off(value);
	}
	else if (name == "exponent")
	{
		frame_data.get_light(light).setExponent(value);
	}
}

void LightWidget::value_changed(QtProperty* property, const QColor& value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "ambient")
	{
		frame_data.get_light(light).setAmbient(colorBTO(value));
	}
	else if (name == "diffuse")
	{
		frame_data.get_light(light).setDiffuse(colorBTO(value));
	}
	else if (name == "specular")
	{
		frame_data.get_light(light).setSpecular(colorBTO(value));
	}
}

void LightWidget::value_changed(QtProperty* property, const QString& value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "name")
	{
		frame_data.get_light(light).setName(value.toStdString());
	}
}

void LightWidget::test()
{
	std::cout << "test" << std::endl;
}
