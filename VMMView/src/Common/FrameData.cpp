/*
 * GlobalConfigParameter.cpp
 *
 *  Created on: 21.08.2009
 *      Author: daniel
 */

#include "FrameData.hpp"
#include <FL/glut.H>
#include "trackball.h"

FrameData::FrameData() :
	translation(0, 0, -2)
{
	trackball(curquat, 0.0, 0.0, 0.0, 0.0);
}

void FrameData::apply_light() const
{
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	for (std::size_t i = 0; i < lights().size(); i++)
	{
		const Light& light = lights()[i];

		if (!light.is_on)
		{
			glDisable(GL_LIGHT0 + i);
			continue;
		}

		glEnable(GL_LIGHT0 + i);
		glLightfv(GL_LIGHT0 + i, GL_AMBIENT, light.ambient.array);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light.diffuse.array);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, light.specular.array);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, light.position.array);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, light.const_att);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, light.lin_att);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light.quad_att);

		if (light.is_spot)
		{
			glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, light.cut_off);
			glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION,
					light.spot_direction.array);
			glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, light.exponent);
		}
		else
		{
			glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180.0f);
		}

		if (light.show_bulp)
		{
			glPushMatrix();
			glTranslatef(light.position.x(), light.position.y(),
					light.position.z());
			glColor3f(1.f, 1.f, 1.f);
			glutSolidSphere(0.01, 4, 4);
			glPopMatrix();
		}
	}
}
