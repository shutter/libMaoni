/*
 * SphereMapping.cpp
 *
 *  Created on: 31 Oct 2009
 *      Author: Daniel Pfeifer
 */

#include <GL/glew.h>
#include <Maoni/RenderAlgorithm.hpp>
#include <Maoni/ShaderProgram.hpp>
#include <Maoni/ScopedLocks.hpp>
#include <Maoni/Texture.hpp>

SHADER_SOURCE(vertex_source,

		varying vec3 normal;

		void main()
		{
			normal = gl_NormalMatrix * gl_Normal;

			gl_Position = ftransform();
		}
);

SHADER_SOURCE(fragment_source,

		uniform sampler2D texture;
		varying vec3 normal;

		void main()
		{
			gl_FragColor = texture2D(texture, vec2(0.5) + 0.5 * normalize(normal).xy);
		}
);

SHADER_PROGRAM(SphereMappingShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(SphereMapping,
		(bool, teapot, true)
		(ShaderProgram, shader, SphereMappingShader())
		(Texture, sphere_texture, "../Models/red.jpeg")
)
{
	ScopedDisable lighting_lock(GL_LIGHTING);
	ScopedEnable texture_2D_lock(GL_TEXTURE_2D);
	ScopedUseProgram shader_lock(shader);

	static Texture* t(0);
	if (!t)
		t = new Texture("../Models/sphere0.jpg");
	ScopedBindTexture texture_lock(*t);

	model.draw();
}
