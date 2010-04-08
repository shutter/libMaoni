/*
 * ImportExport.cpp
 *
 *  Created on: 08.04.2010
 *      Author: daniel
 */

#include "ImportExport.hpp"
#include "FrameData.hpp"

#include <QFile>
#include <QTextStream>
#include <QDomElement>

#include <boost/la/all.hpp>
using namespace boost::la;

static QDomElement LightToNode(QDomDocument &d, const Light &l)
{
	QDomElement cn = d.createElement("light");

	cn.setAttribute("pos_x", l.position | X);
	cn.setAttribute("pos_y", l.position | Y);
	cn.setAttribute("pos_z", l.position | Z);

	cn.setAttribute("ambient_r", l.ambient.red());
	cn.setAttribute("ambient_g", l.ambient.green());
	cn.setAttribute("ambient_b", l.ambient.blue());
	cn.setAttribute("ambient_a", l.ambient.alpha());

	cn.setAttribute("diffuse_r", l.diffuse.red());
	cn.setAttribute("diffuse_g", l.diffuse.green());
	cn.setAttribute("diffuse_b", l.diffuse.blue());
	cn.setAttribute("diffuse_a", l.diffuse.alpha());

	cn.setAttribute("specular_r", l.specular.red());
	cn.setAttribute("specular_g", l.specular.green());
	cn.setAttribute("specular_b", l.specular.blue());
	cn.setAttribute("specular_a", l.specular.alpha());

	cn.setAttribute("const_att", l.const_att);
	cn.setAttribute("lin_att", l.lin_att);
	cn.setAttribute("quad_att", l.quad_att);

	cn.setAttribute("is_spot", l.is_spot);

	cn.setAttribute("spot_x", l.spot_direction | X);
	cn.setAttribute("spot_y", l.spot_direction | Y);
	cn.setAttribute("spot_z", l.spot_direction | Z);

	cn.setAttribute("cut_off", l.cut_off);
	cn.setAttribute("exponent", l.exponent);

	cn.setAttribute("is_on", l.enabled);
	cn.setAttribute("show_bulp", l.show_bulp);

	return cn;
}

int export_lights(std::string const& filename, FrameData const& framedata)
{
	QDomDocument doc("LightConfig");
	QDomElement root = doc.createElement("lightconfig");
	doc.appendChild(root);

	for (size_t i = 0; i < framedata.num_lights(); i++)
	{
		root.appendChild(LightToNode(doc, framedata.light(i)));
	}

	QFile file(filename.c_str());
	if (!file.open(QIODevice::WriteOnly))
		return -1;

	QTextStream ts(&file);
	ts << doc.toString();

	file.close();
	return 0;
}

int import_lights(std::string const& filename, FrameData & framedata)
{
	QDomDocument doc("LightConfig");
	QFile file(filename.c_str());
	if (!file.open(QIODevice::ReadOnly))
	{
		return -1;
	}
	if (!doc.setContent(&file))
	{
		file.close();
		return -2;
	}
	file.close();
	QDomElement root = doc.documentElement();
	if (root.tagName() != "lightconfig")
	{
		return -3;
	}
	QDomNode n = root.firstChild();

	std::size_t light_id = 0;

	while (!n.isNull())
	{
		QDomElement e = n.toElement();
		if (!e.isNull())
		{
			if (e.tagName() == "light")
			{
				Light& l = framedata.light(light_id++);

				l.position = Vector3(e.attribute("pos_x", "").toFloat(),
						e.attribute("pos_y", "").toFloat(), e.attribute(
								"pos_z", "").toFloat());

				l.ambient = Color(e.attribute("ambient_r", "").toFloat(),
						e.attribute("ambient_g", "").toFloat(), e.attribute(
								"ambient_b", "").toFloat(), e.attribute(
								"ambient_a", "").toFloat());

				l.diffuse = Color(e.attribute("diffuse_r", "").toFloat(),
						e.attribute("diffuse_g", "").toFloat(), e.attribute(
								"diffuse_b", "").toFloat(), e.attribute(
								"diffuse_a", "").toFloat());

				l.specular = Color(e.attribute("specular_r", "").toFloat(),
						e.attribute("specular_g", "").toFloat(), e.attribute(
								"specular_b", "").toFloat(), e.attribute(
								"specular_a", "").toFloat());

				l.const_att = e.attribute("const_att", "").toFloat();
				l.lin_att = e.attribute("lin_att", "").toFloat();
				l.quad_att = e.attribute("quad_att", "").toFloat();

				l.is_spot = e.attribute("is_spot", "").toInt();

				l.spot_direction = Vector3(e.attribute("spot_x", "").toFloat(),
						e.attribute("spot_y", "").toFloat(), e.attribute(
								"spot_z", "").toFloat());

				l.cut_off = e.attribute("cut_off", "").toFloat();
				l.exponent = e.attribute("exponent", "").toFloat();

				l.enabled = e.attribute("is_spot", "").toInt();
				l.show_bulp = e.attribute("is_spot", "").toInt();
			}
		}

		n = n.nextSibling();
	}

	return 0;
}
