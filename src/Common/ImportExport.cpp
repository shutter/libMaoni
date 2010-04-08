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

	cn.setAttribute("pos_x", l.getPosition() | X);
	cn.setAttribute("pos_y", l.getPosition() | Y);
	cn.setAttribute("pos_z", l.getPosition() | Z);

	cn.setAttribute("ambient_r", l.getAmbient().red());
	cn.setAttribute("ambient_g", l.getAmbient().green());
	cn.setAttribute("ambient_b", l.getAmbient().blue());
	cn.setAttribute("ambient_a", l.getAmbient().alpha());

	cn.setAttribute("diffuse_r", l.getDiffuse().red());
	cn.setAttribute("diffuse_g", l.getDiffuse().green());
	cn.setAttribute("diffuse_b", l.getDiffuse().blue());
	cn.setAttribute("diffuse_a", l.getDiffuse().alpha());

	cn.setAttribute("specular_r", l.getSpecular().red());
	cn.setAttribute("specular_g", l.getSpecular().green());
	cn.setAttribute("specular_b", l.getSpecular().blue());
	cn.setAttribute("specular_a", l.getSpecular().alpha());

	cn.setAttribute("const_att", l.getConst_att());
	cn.setAttribute("lin_att", l.getLin_att());
	cn.setAttribute("quad_att", l.getQuad_att());

	cn.setAttribute("is_spot", l.getIs_spot());

	cn.setAttribute("spot_x", l.getSpot_direction() | X);
	cn.setAttribute("spot_y", l.getSpot_direction() | Y);
	cn.setAttribute("spot_z", l.getSpot_direction() | Z);

	cn.setAttribute("cut_off", l.getCut_off());
	cn.setAttribute("exponent", l.getExponent());

	cn.setAttribute("is_on", l.getIs_on());
	cn.setAttribute("show_bulp", l.getShow_bulp());

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

				l.setPosition(Vector3(e.attribute("pos_x", "").toFloat(),
						e.attribute("pos_y", "").toFloat(), e.attribute(
								"pos_z", "").toFloat()));

				l.setAmbient(Color(e.attribute("ambient_r", "").toFloat(),
						e.attribute("ambient_g", "").toFloat(), e.attribute(
								"ambient_b", "").toFloat(), e.attribute(
								"ambient_a", "").toFloat()));

				l.setDiffuse(Color(e.attribute("diffuse_r", "").toFloat(),
						e.attribute("diffuse_g", "").toFloat(), e.attribute(
								"diffuse_b", "").toFloat(), e.attribute(
								"diffuse_a", "").toFloat()));

				l.setSpecular(Color(e.attribute("specular_r", "").toFloat(),
						e.attribute("specular_g", "").toFloat(), e.attribute(
								"specular_b", "").toFloat(), e.attribute(
								"specular_a", "").toFloat()));

				l.setConst_att(e.attribute("const_att", "").toFloat());
				l.setLin_att(e.attribute("lin_att", "").toFloat());
				l.setQuad_att(e.attribute("quad_att", "").toFloat());

				l.setIs_spot(e.attribute("is_spot", "").toInt());

				l.setSpot_direction(Vector3(
						e.attribute("spot_x", "").toFloat(), e.attribute(
								"spot_y", "").toFloat(), e.attribute("spot_z",
								"").toFloat()));

				l.setCut_off(e.attribute("cut_off", "").toFloat());
				l.setExponent(e.attribute("exponent", "").toFloat());

				l.setIs_on(e.attribute("is_spot", "").toInt());
				l.setShow_bulp(e.attribute("is_spot", "").toInt());
			}
		}

		n = n.nextSibling();
	}

	return 0;
}
