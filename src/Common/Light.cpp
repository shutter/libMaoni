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
		glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, spot_direction.array);
		glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, exponent);
	}
	else
	{
		glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180.0);
		GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
		glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, spot_direction);
		glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, 0.0);
	}

	if (show_bulp)
	{
		glColor3f(1.f, 1.f, 1.f);

		glBegin(GL_QUAD_STRIP);
		{
			glVertex3fv(light_box[0].array);
			glVertex3fv(light_box[1].array);
			glVertex3fv(light_box[2].array);
			glVertex3fv(light_box[3].array);
			glVertex3fv(light_box[6].array);
			glVertex3fv(light_box[7].array);
			glVertex3fv(light_box[4].array);
			glVertex3fv(light_box[5].array);
			glVertex3fv(light_box[0].array);
			glVertex3fv(light_box[1].array);
		}
		glEnd();

		glBegin(GL_QUADS);
		{
			glVertex3fv(light_box[0].array);
			glVertex3fv(light_box[4].array);
			glVertex3fv(light_box[6].array);
			glVertex3fv(light_box[2].array);

			glVertex3fv(light_box[1].array);
			glVertex3fv(light_box[5].array);
			glVertex3fv(light_box[7].array);
			glVertex3fv(light_box[4].array);
		}
		glEnd();

		if (is_spot)
		{
			glBegin(GL_LINES);
			glVertex3fv(position);
			glVertex3f(position.x() + spot_direction.x(),position.y() + spot_direction.y(),position.z() + spot_direction.z());
			glEnd();
		}
	}
}

