/*
 * FixedFunction.cpp
 *
 *  Created on: 23.07.2009
 *      Author: daniel
 */

#include "VMMView/RenderAlgorithm.hpp"
#include "VMMView/Color.hpp"
#include <FL/glut.H>

RENDER_ALGORITHM(FixedFunction,
		(bool, wired, false)
		(bool, bounding_sphere, false)
		(bool, model_color, true)
		(Color, rgba_color, Color(0.9f, 0.1f, 0.2f, 0.5f))
		(Color, ambient, Color(0.24725, 0.1995, 0.0745, 1.0))
		(Color, diffuse, Color(0.75164, 0.60648, 0.22648, 1.0))
		(Color, specular, Color(0.628281, 0.555802, 0.366065, 0.0))
		(float, shininess, 51.2))
{
	if (!model_color)
		glColor4fv(rgba_color);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (bounding_sphere && !wired)
		glutSolidSphere(model.getBoundingSphereRadius(), 100, 100);
	else if (bounding_sphere && wired)
		glutWireSphere(model.getBoundingSphereRadius(), 100, 100);

	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < model.triangles.size(); i++)
	{
		if (model_color)
			glColor4fv(model.vertices[model.triangles[i][0]].color.array);
		glNormal3fv(model.vertices[model.triangles[i][0]].normal.array);
		glVertex3fv(model.vertices[model.triangles[i][0]].position.array);

		if (model_color)
			glColor4fv(model.vertices[model.triangles[i][1]].color.array);
		glNormal3fv(model.vertices[model.triangles[i][1]].normal.array);
		glVertex3fv(model.vertices[model.triangles[i][1]].position.array);

		if (model_color)
			glColor4fv(model.vertices[model.triangles[i][2]].color.array);
		glNormal3fv(model.vertices[model.triangles[i][2]].normal.array);
		glVertex3fv(model.vertices[model.triangles[i][2]].position.array);

	}

	glEnd();

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
