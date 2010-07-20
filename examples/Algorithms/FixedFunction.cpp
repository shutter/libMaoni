/*
 * A simple fixed function algorithm
 */

#include <GL/glew.h>
#include <Maoni.hpp>
#include "../Loaders/VBOModel.hpp"

#include <boost/la/all.hpp>
using namespace boost::la;

static const float normal_length = 0.05f;

RENDER_ALGORITHM(FixedFunction,
		(bool, wired, false)
		(bool, vertex_normals, false)
		(Color, ambient, Color(0.24725, 0.1995, 0.0745, 1.0))
		(Color, diffuse, Color(0.75164, 0.60648, 0.22648, 1.0))
		(Color, specular, Color(0.628281, 0.555802, 0.366065, 0.0))
		(float, shininess, 51.2))
{
	ScopedEnable color_material_lock(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

	if (wired) // set triangle draw to edges only
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model.draw();

	if (vertex_normals)
	{
		try
		{
			const VBOModel& vbo_model = dynamic_cast<const VBOModel&> (model);
			std::vector<Vertex> const& vertices = vbo_model.get_vertices();
			glBegin(GL_LINES);
			for (size_t i = 0; i < vertices.size(); i++)
			{
				glColor3f(0.f, 1.f, 0.f);
				glVertex3fv(vertices[i].position);
				glVertex3fv((vertices[i].position + vertices[i].normal
						* normal_length));
			}
			glEnd();
		} catch (...)
		{
			// cast failed
		}
	}

	if (wired) // reset triangles draw to filled
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
