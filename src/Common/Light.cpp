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
	if (is_on)
	{
		glEnable(GL_LIGHT0 + i);
		glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, position);
		glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION, const_att);
		glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION, lin_att);
		glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, quad_att);

		if (is_spot)
		{
			glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, cut_off);
			glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, spot_direction);
			glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, exponent);
		}
		else
		{
			glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180.0);
			GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
			glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, spot_direction);
			glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, 0.0);
		}

	}
}

