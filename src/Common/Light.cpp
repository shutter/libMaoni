/*
 * Light.hpp
 *
 *  Created on: 7 Aug 2009
 *      Author: stefan
 */

#include "Light.hpp"
#include <GL/glew.h>

void Light::apply(int i) const
{
	if (!is_on)
		return;

	glEnable(GL_LIGHT0 + i);

	// colors
	glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular);

	// attenuation
	glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, const_att);
	glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, lin_att);
	glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, quad_att);

	if (is_spot)
	{
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, cut_off);
		glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, spot_direction);
		glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, exponent);
	}

	GLfloat pos[] = { position.x(), position.y(), position.z(), is_spot };
	glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);
}
