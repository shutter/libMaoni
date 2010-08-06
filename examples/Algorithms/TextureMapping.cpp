/*
 *      inspired by http://www.ozone3d.net/tutorials/glsl_texturing.php
 */

#include <Maoni.hpp>

SHADER_SOURCE(vertex_source, (version 120),

		void main()
		{
			gl_TexCoord[0] = gl_MultiTexCoord0;
			gl_Position = ftransform();
		}

);

SHADER_SOURCE(fragment_source, (version 120),

		uniform sampler2D color_map;

		void main(void)
		{
			gl_FragColor = texture2D(color_map, gl_TexCoord[0].st);
		}

);

SHADER_PROGRAM(TextureMappingShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(TextureMapping,
		(ShaderProgram, shader, TextureMappingShader())
		(Texture, color_texture, "../examples/Models/sphere3.jpg")
)
{
	ScopedDisable lighting_lock(GL_LIGHTING);
	ScopedEnable color_map_2D_lock(GL_TEXTURE_2D);
	ScopedBindTexture color_map_lock(color_texture);
	ScopedUseProgram shader_lock(shader);

	GLint width = 0, height = 0;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	// fit the texture into the (-1,-1) to (1,1) quad retaining the aspect ratio
	if (width > height)
	{
		float ratio = (height / float(width));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -ratio, 0.0f); // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -ratio, 0.0f); // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, ratio, 0.0f); // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, ratio, 0.0f); // Top Left Of The Texture and Quad
		glEnd();
	}
	else
	{
		float ratio = (width / float(height));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-ratio, -1.0f, 0.0f); // Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(ratio, -1.0f, 0.0f); // Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(ratio, 1.0f, 0.0f); // Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-ratio, 1.0f, 0.0f); // Top Left Of The Texture and Quad
		glEnd();

	}

}
