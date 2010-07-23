/*
 * A simple comic style surface shader
 */

#include <GL/glew.h>
#include <Maoni.hpp>
#include "../Loaders/VBOModel.hpp"

SHADER_SOURCE(vertex_source, (version 120),
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
		(bool, rank_colors, false)
		(Color, comic_color, Color(0.4, 0.7, 0.5, 1.0))
		(int, increments, 7)
		(ShaderProgram, shader, ComicStyleShader()))
{

	ScopedUseProgram shader_lock(shader);

	GLint loc_color = glGetUniformLocation(shader, "comic_color");

	float red = comic_color.red();
	float green = comic_color.green();
	float blue = comic_color.blue();
	if (rank_colors)
	{
		try
		{
			const VBOModel& vbo_model = dynamic_cast<const VBOModel&> (model);

			switch (vbo_model.getMyRank())
			{
			case 0: // yellow
				red = 1.0;
				green = 1.0;
				blue = 0.0;
				break;
			case 1: // red
				red = 1.0;
				green = 0.0;
				blue = 0.0;
				break;
			case 2: // magenta
				red = 1.0;
				green = 0.0;
				blue = 1.0;
				break;
			case 3: // blue
				red = 0.0;
				green = 0.0;
				blue = 1.0;
				break;
			case 4: // cyan
				red = 0.0;
				green = 1.0;
				blue = 1.0;
				break;
			case 5: // green
				red = 0.0;
				green = 1.0;
				blue = 0.0;
				break;
			case 6: // orange
				red = 1.0;
				green = 0.5;
				blue = 0.0;
				break;
			case 7: // purple
				red = 0.5;
				green = 0.0;
				blue = 0.5;
				break;
			default:
				;
			}

		} catch (...)
		{
			// cast failed
		}
	}

	glUniform4f(loc_color, red, green, blue, 1.0);

	GLint loc_increments = glGetUniformLocation(shader, "increments");
	glUniform1i(loc_increments, increments);

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model.draw();

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
