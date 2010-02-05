/*
 * ComicStyle.cpp
 *
 *  Created on: 29 Jul 2009
 *      Author: stefan
 */

#include <GL/glew.h>
#include <Maoni/RenderAlgorithm.hpp>
#include <Maoni/ShaderProgram.hpp>
#include <Maoni/ScopedLocks.hpp>

SHADER_SOURCE(vertex_source,
		varying vec3 lightDir;
		varying vec3 normal;

		void main()
		{
			lightDir = normalize(vec3(gl_LightSource[0].position));
			normal = gl_NormalMatrix * gl_Normal;

			gl_Position = ftransform();
		}
);

SHADER_SOURCE(fragment_source,
		varying vec3 lightDir;
		varying vec3 normal;

		void main()
		{
			float intensity;
			vec4 color;

			// normalizing the lights position to be on the safe side

			vec3 n = normalize(normal);

			intensity = dot(lightDir, n);

			if (intensity > 0.95)
			{
				color = vec4(1.0, 0.5, 0.5, 1.0);
			}
			else if (intensity > 0.5)
			{
				color = vec4(0.6, 0.3, 0.3, 1.0);
			}
			else if (intensity > 0.25)
			{
				color = vec4(0.4, 0.2, 0.2, 1.0);
			}
			else
			{
				color = vec4(0.2, 0.1, 0.1, 1.0);
			}

			gl_FragColor = color;
		}
);

SHADER_PROGRAM(ComicStyleShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(ComicStyle,
		(bool, wired, false)
		(bool, bounding_sphere, false)
		(ShaderProgram, shader, ComicStyleShader()))
{
	ScopedUseProgram shader_lock(shader);

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//	if (bounding_sphere && !wired)
//		glutSolidSphere(model.getBoundingSphereRadius(), 100, 100);
//	else if (bounding_sphere && wired)
//		glutWireSphere(model.getBoundingSphereRadius(), 100, 100);

	glBegin(GL_TRIANGLES);

	for (size_t i = 0; i < model.triangles.size(); i++)
	{
		glNormal3fv(model.vertices[model.triangles[i][0]].normal.array);
		glVertex3fv(model.vertices[model.triangles[i][0]].position.array);

		glNormal3fv(model.vertices[model.triangles[i][1]].normal.array);
		glVertex3fv(model.vertices[model.triangles[i][1]].position.array);

		glNormal3fv(model.vertices[model.triangles[i][2]].normal.array);
		glVertex3fv(model.vertices[model.triangles[i][2]].position.array);
	}

	glEnd();

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
