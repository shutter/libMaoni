/*
 * A simple fixed function algorithm
 */

#include <Maoni.hpp>
#include "../Loaders/VBOModel.hpp"

#include <boost/la/all.hpp>
using namespace boost::la;

static const float normal_length = 0.05f;

RENDER_ALGORITHM(FixedFunction,
		(bool, wired, false)
		(bool, vertex_normals, false)
		(Color, normal_color, Color(0.0, 7.0, 0.0, 1.0))
		(Color, ambient, Color(0.75, 0.75, 0.0, 1.0))
		(Color, diffuse, Color(0.75, 0.75, 0.0, 1.0))
		(Color, specular, Color(1.0, 1.0, 1.0, 1.0))
		(Color, emission, Color(0.0, 0.0, 0.0, 1.0))
		(float, shininess, 50.0))
{
	ScopedEnable color_material_lock(GL_COLOR_MATERIAL);
	glColorMaterial(GL_AMBIENT_AND_DIFFUSE, GL_DIFFUSE);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

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
				glColor4fv(normal_color);
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
