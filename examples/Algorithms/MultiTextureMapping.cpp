/*
 *      from http://www.lighthouse3d.com/opengl/glsl/index.php?textureMulti
 */

#include <Maoni.hpp>
#include <iostream>

SHADER_SOURCE(vertex_source,(),

		varying vec3 lightDir;
		varying vec3 normal;

		void main()
		{

			normal = normalize(gl_NormalMatrix * gl_Normal);
			lightDir = normalize(vec3(gl_LightSource[0].position));

			gl_TexCoord[0] = gl_MultiTexCoord0;
			gl_Position = ftransform();
		}
);

SHADER_SOURCE(fragment_source,(),

		varying vec3 lightDir;
		varying vec3 normal;
		uniform sampler2D tex;
		uniform sampler2D l3d;

		void main()
		{
			vec3 ct;
			vec3 cf;
			vec3 c;
			vec4 texel;
			float intensity;
			float at;
			float af;
			float a;

			intensity = max(dot(lightDir,normalize(normal)),0.0);

			cf = intensity * (gl_FrontMaterial.diffuse).rgb +
			gl_FrontMaterial.ambient.rgb;
			af = gl_FrontMaterial.diffuse.a;

			texel = texture2D(tex,gl_TexCoord[0].st);

			ct = texel.rgb;
			at = texel.a;

			c = cf * ct;
			a = af * at;

			float coef = smoothstep(1.0,0.2,intensity);
			c += coef * vec3(texture2D(l3d,gl_TexCoord[0].st));

			gl_FragColor = vec4(c, a);
		}
);

SHADER_PROGRAM(MultiTextureShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(MultiTexture,
		(ShaderProgram, shader, MultiTextureShader())
		(Texture, tex, "../examples/Models/crate.jpg")
		(Texture, l3d, "../examples/Models/l3d.jpg")
		(Color, ambient, Color(0.24725, 0.1995, 0.0745, 1.0))
		(Color, diffuse, Color(0.75164, 0.60648, 0.22648, 1.0))
		(Color, specular, Color(0.628281, 0.555802, 0.366065, 0.0))
		(Color, emission, Color(0.0, 0.0, 0.0, 0.0))
		(float, shininess, 51.2)
)
{
	ScopedEnable material_color_lock(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	ScopedDisable lighting_lock(GL_LIGHTING);
	ScopedEnable tex_2D_lock(GL_TEXTURE_2D);
	ScopedBindTexture tex_lock(tex, GL_TEXTURE0);
	ScopedBindTexture l3d_lock(l3d, GL_TEXTURE1);
	ScopedUseProgram shader_lock(shader);

	glUniform1i(glGetUniformLocation(shader, "tex"), 0);
	glUniform1i(glGetUniformLocation(shader, "l3d"), 1);

	static bool test = false;
	if (!test)
	{
		int tunits;
		glGetIntegerv(GL_MAX_TEXTURE_UNITS, &tunits);

		int iunits;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &iunits);

		std::cout << "avaible units in fixed function pipeline: " << tunits
				<< ", and in fragment processing: " << iunits << std::endl;

		test = true;
	}

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f); // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f); // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f); // Top Left Of The Texture and Quad
	glEnd();
}
