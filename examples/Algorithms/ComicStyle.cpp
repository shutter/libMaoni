/*
 * ComicStyle.cpp
 *
 *  Created on: 11 Mar 2010
 *      Author: stefan
 */

#include <GL/glew.h>
#include <Maoni/RenderAlgorithm.hpp>
#include <Maoni/ShaderProgram.hpp>
#include <Maoni/ScopedLocks.hpp>

SHADER_SOURCE(vertex_source, (version 130),
		varying vec3 lightDir;
		varying vec3 normal;

		void main()
		{
			lightDir = normalize(vec3(gl_LightSource[0].position));
			normal = gl_NormalMatrix * gl_Normal;

			gl_Position = ftransform();
		}
);

SHADER_SOURCE(fragment_source, (version 130),

		varying vec3 lightDir;
		varying vec3 normal;
		uniform vec4 comic_color;
		uniform int increments;

		void main()
		{
			float intensity;
			vec4 color;

			// normalizing the lights position to be on the safe side

			vec3 n = normalize(normal);

			intensity = dot(lightDir, n);

			color = (round(intensity*increments)/increments) * comic_color;

			gl_FragColor = color;
		}
);

SHADER_PROGRAM(ComicStyleShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(ComicStyle,
		(bool, wired, false)
		(bool, bounding_sphere, false)
		(Color, comic_color, Color(0.4, 0.7, 0.5, 1.0))
		(int, increments, 7)
		(ShaderProgram, shader, ComicStyleShader()))
{

	ScopedUseProgram shader_lock(shader);

	GLint loc_color = glGetUniformLocation(shader, "comic_color");
	glUniform4f(loc_color, comic_color.red(), comic_color.green(),
			comic_color.blue(), 1.0);

	GLint loc_increments = glGetUniformLocation(shader, "increments");
	glUniform1i(loc_increments, increments);

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model.draw();

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
