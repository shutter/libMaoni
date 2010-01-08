/*
 * Teapot.cpp
 *
 *  Created on: Jul 27, 2009
 *      Author: dpfeifer
 */

#include "VMMView/RenderAlgorithm.hpp"
#include <FL/glut.H>

RENDER_ALGORITHM(Teapot,
		(bool, wired, false)
		(bool, flat, false)
		(bool, POI, true)
		(Color, color,)
		(Color, ambient, Color(0.24725, 0.1995, 0.0745, 1.0))
		(Color, diffuse, Color(0.75164, 0.60648, 0.22648, 1.0))
		(Color, specular, Color(0.628281, 0.555802, 0.366065, 0.0))
		(float, shininess, 51.2))
{
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

	glShadeModel(flat ? GL_FLAT : GL_SMOOTH);

	if (POI)
	{
		glPushMatrix();
		glColor3f(1.f, 1.f, 1.f);
		glutSolidSphere(0.01, 4, 4);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.f, 0.f, 0.f);
		glColor3f(1.f, 0.f, 0.f);
		glutSolidSphere(0.01, 4, 4);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.f, 1.f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glutSolidSphere(0.01, 4, 4);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.f, 0.f, 1.f);
		glColor3f(0.f, 0.f, 1.f);
		glutSolidSphere(0.01, 4, 4);
		glPopMatrix();
	}

	glColor4fv(color);

	if (wired)
		glutWireTeapot(0.5);
	else
		glutSolidTeapot(0.5);
}
