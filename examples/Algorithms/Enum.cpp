/*
 * Enum.cpp
 *
 *  Created on: 08.05.2010
 *      Author: daniel
 */

#include <GL/glew.h>
#include <Maoni.hpp>
#include <cmath>
#include "Teaset.h"

static void qglviewer_spiral()
{
	const float nbSteps = 200.0;

	glBegin(GL_QUAD_STRIP);

	for (int i = 0; i < nbSteps; ++i)
	{
		const float ratio = i / nbSteps;
		const float angle = 21.f * ratio;
		const float c = std::cos(angle);
		const float s = std::sin(angle);
		const float r1 = 1.f - 0.8f * ratio;
		const float r2 = 0.8f - 0.8f * ratio;
		const float alt = ratio - 0.5f;
		const float nor = 0.5f;
		const float up = std::sqrt(1.f - nor * nor);
		glColor3f(1.f - ratio, 0.2f, ratio);
		glNormal3f(nor * c, up, nor * s);
		glVertex3f(r1 * c, alt, r1 * s);
		glVertex3f(r2 * c, alt + 0.05f, r2 * s);
	}

	glColor3f(1.f, 1.f, 1.f);
	glEnd();
}

ENUM(Select,
	(Model)
	(Spiral)
	(SolidTeacup)
	(SolidTeapot)
	(SolidTeaspoon)
	(WireTeacup)
	(WireTeapot)
	(WireTeaspoon)
);

RENDER_ALGORITHM(EnumExample, (Select, select, Select::Model))
{
	switch (select)
	{
	case Select::Spiral:
		qglviewer_spiral();
		break;
	case Select::SolidTeacup:
		solid_teacup(1.f);
		break;
	case Select::SolidTeapot:
		solid_teapot(1.f);
		break;
	case Select::SolidTeaspoon:
		solid_teaspoon(1.f);
		break;
	case Select::WireTeacup:
		wire_teacup(1.f);
		break;
	case Select::WireTeapot:
		wire_teapot(1.f);
		break;
	case Select::WireTeaspoon:
		wire_teaspoon(1.f);
		break;
	case Select::Model:
	default:
		model.draw();
	}
}
