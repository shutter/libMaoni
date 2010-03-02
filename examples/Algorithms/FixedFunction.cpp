/*
 * FixedFunction.cpp
 *
 *  Created on: 23.07.2009
 *      Author: daniel
 */

#include <GL/glew.h>
#include <Maoni/RenderAlgorithm.hpp>
#include <Maoni/Color.hpp>

RENDER_ALGORITHM(FixedFunction,
		(bool, wired, false)
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

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model.draw();

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
