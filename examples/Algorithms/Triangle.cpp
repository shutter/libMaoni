/*
 * A simple fixed function triangle algorithm
 */

#include <Maoni.hpp>

RENDER_ALGORITHM(Triangle,
		(Color, Color1, Color(1.0f, 0.0f, 0.0f, 1.0f))
		(Color, Color2, Color(0.0f, 1.0f, 0.0f, 1.0f))
		(Color, Color3, Color(0.0f, 0.0f, 1.0f, 1.0f))
)
{
	glBegin(GL_TRIANGLES);				// Begin Drawing Triangles
	{
		glColor4fv(Color1); 			// Set The Color To Red
		glVertex3f( 0.0f, 1.0f, 0.0f); 	// Move Up One Unit From Center (Top Point)
		glColor4fv(Color2); 			// Set The Color To Green
		glVertex3f(-1.0f,-1.0f, 0.0f); 	// Left And Down One Unit (Bottom Left)
		glColor4fv(Color3); 			// Set The Color To Blue
		glVertex3f( 1.0f,-1.0f, 0.0f); 	// Right And Down One Unit (Bottom Right)
	}
	glEnd();
}
