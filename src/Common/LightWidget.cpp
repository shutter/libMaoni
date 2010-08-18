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

#include "LightWidget.hpp"
#include "../Common/FrameData.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include <qteditorfactory.h>

#include <boost/la/all.hpp>
using namespace boost::la;

LightWidget::LightWidget(FrameData& framedata, QWidget *parent) :
	QWidget(parent), framedata(framedata), current_id(0)
{
	QVBoxLayout* layout = new QVBoxLayout;

	light_chooser = new QComboBox;
	update_combobox();
	light_chooser->show();
	layout->addWidget(light_chooser);

	property_browser = new QtTreePropertyBrowser;
	layout->addWidget(property_browser);

	setLayout(layout);
	setWindowTitle("Light Control");

	connect(light_chooser, SIGNAL(activated(int)), this,
			SLOT(choose(int)));

	bool_manager = new QtBoolPropertyManager(this);
	double_manager = new QtDoublePropertyManager(this);
	color_manager = new QtColorPropertyManager(this);
	vector3d_manager = new QVector3DPropertyManager(this);
	group_manager = new QtGroupPropertyManager(this);

	is_on = bool_manager->addProperty("activate");
	is_on->setToolTip("Turn light on and off");
	show_bulp = bool_manager->addProperty("show bulp");
	show_bulp->setToolTip("Draw the light source");
	position = vector3d_manager->addProperty("position");
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
	spot_dir = vector3d_manager->addProperty("spot_dir");
	cut_off = double_manager->addProperty("cut off angle");
	cut_off->setToolTip(
			"Specifies the angle between the axis of the cone and a ray along the edge of the cone. The angle of the cone at the apex is then twice this value.");
	double_manager->setRange(cut_off, 0.0, 90.0);
	exponent = double_manager->addProperty("exponent");

	QtDoubleSpinBoxFactory* double_factory = new QtDoubleSpinBoxFactory(this);
	QtCheckBoxFactory* bool_factory = new QtCheckBoxFactory(this);
	QtSpinBoxFactory* int_factory = new QtSpinBoxFactory(this);
	QtColorEditorFactory* color_factory = new QtColorEditorFactory(this);

	property_browser->setFactoryForManager(bool_manager, bool_factory);
	property_browser->setFactoryForManager(double_manager, double_factory);
	property_browser->setFactoryForManager(color_manager, color_factory);
	property_browser->setFactoryForManager(
			color_manager->subIntPropertyManager(), int_factory);
	property_browser->setFactoryForManager(
			vector3d_manager->subDoublePropertyManager(), double_factory);

	connect(bool_manager, SIGNAL(valueChanged(QtProperty*, bool)), this,
			SLOT(value_changed(QtProperty*, bool)));
	connect(double_manager, SIGNAL(valueChanged(QtProperty*, double)), this,
			SLOT(value_changed(QtProperty*, double)));
	connect(color_manager, SIGNAL(valueChanged(QtProperty*, QColor)), this,
			SLOT(value_changed(QtProperty*, QColor)));
	connect(vector3d_manager, SIGNAL(valueChanged(QtProperty*, Vec3)), this,
			SLOT(value_changed(QtProperty*, Vec3)));

	light_chooser->setCurrentIndex(0);
	choose(0);
	property_browser->show();
}

void LightWidget::update_combobox()
{
	light_chooser->clear();

	QStringList list;
	for (unsigned int i = 0; i < framedata.num_lights(); ++i)
		list.append(QString("Light %1").arg(i));

	light_chooser->addItems(list);
}

void LightWidget::reload()
{
	choose(current_id);
}

void LightWidget::choose(int i)
{
	current_id = i;
	const FrameData& framedatac = framedata;
	const Light& light = framedatac.light(current_id);

	property_browser->clear();

	bool_manager->setValue(is_on, light.enabled);
	property_browser->addProperty(is_on);

	show_bulp->setEnabled(light.enabled);
	position->setEnabled(light.enabled);
	ambient->setEnabled(light.enabled);
	diffuse->setEnabled(light.enabled);
	specular->setEnabled(light.enabled);
	attenuation->setEnabled(light.enabled);
	is_spot->setEnabled(light.enabled);
	spot_dir->setEnabled(light.enabled);
	cut_off->setEnabled(light.enabled);
	exponent->setEnabled(light.enabled);

	bool_manager->setValue(show_bulp, light.show_bulp);
	property_browser->addProperty(show_bulp);
	vector3d_manager->setValue(position, //
			Vec3(light.position | X, light.position | Y, light.position
					| Z));
	property_browser->addProperty(position);
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

	if (current_id != 0)
	{
		bool_manager->setValue(is_spot, light.is_spot);
		property_browser->addProperty(is_spot);
		vector3d_manager->setValue(spot_dir, //
				Vec3(light.spot_direction | X, light.spot_direction | Y,
						light.spot_direction | Z));
		property_browser->addProperty(spot_dir);
		double_manager->setValue(cut_off, light.cut_off);
		property_browser->addProperty(cut_off);
		double_manager->setValue(exponent, light.exponent);
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
	return Color(byte.red() / 255.0, byte.green() / 255.0, byte.blue() / 255.0,
			byte.alpha() / 255.0);
}

void LightWidget::value_changed(QtProperty* property, bool value)
{
	QString name = property->propertyName();
	if (name == "activate")
	{
		framedata.light(current_id).enabled = value;
		choose(light_chooser->currentIndex());
	}
	else if (name == "show bulp")
	{
		framedata.light(current_id).show_bulp = value;
	}
	else if (name == "spot light")
	{
		framedata.light(current_id).is_spot = value;
	}
}

void LightWidget::value_changed(QtProperty* property, double value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "constant attenuation")
	{
		framedata.light(current_id).const_att = value;
	}
	else if (name == "linear attenuation")
	{
		framedata.light(current_id).lin_att = value;
	}
	else if (name == "quadratic attenuation")
	{
		framedata.light(current_id).quad_att = value;
	}
	else if (name == "cut off angle")
	{
		framedata.light(current_id).cut_off = value;
	}
	else if (name == "exponent")
	{
		framedata.light(current_id).exponent = value;
	}
}

void LightWidget::value_changed(QtProperty* property, const QColor& value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "ambient")
	{
		framedata.light(current_id).ambient = colorBTO(value);
	}
	else if (name == "diffuse")
	{
		framedata.light(current_id).diffuse = colorBTO(value);
	}
	else if (name == "specular")
	{
		framedata.light(current_id).specular = colorBTO(value);
	}
}

void LightWidget::value_changed(QtProperty* property, const Vec3& value)
{
	std::string name = property->propertyName().toStdString();
	if (name == "position")
	{

		framedata.light(current_id).position = //
				Vec3(value | X, value | Y, value | Z);
	}
	else if (name == "spot_dir")
	{
		framedata.light(current_id).spot_direction = //
				Vec3(value | X, value | Y, value | Z);
	}
}

void LightWidget::update_browser()
{
	update_combobox();
	choose(0);
}
