/*
 * SphereMapping.cpp
 *
 *  Created on: 31 Oct 2009
 *      Author: Daniel Pfeifer
 */

#include <GL/glew.h>
#include <Maoni.hpp>

SHADER_SOURCE(vertex_source, (version 130),

		varying vec3 normal;

		void main()
		{
			normal = gl_NormalMatrix * gl_Normal;

			gl_Position = ftransform();
		}
);

SHADER_SOURCE(fragment_source, (version 130),

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

ENUM(Object, (Teacup)(Teaspoon)(Teapot)(Model));

RENDER_ALGORITHM(SphereMapping,
		(Object, object, Object::Teapot)
		(ShaderProgram, shader, SphereMappingShader())
		(Texture, sphere_texture, "./Models/sphere3.jpg")
)
{
	ScopedDisable lighting_lock(GL_LIGHTING);
	ScopedEnable texture_2D_lock(GL_TEXTURE_2D);
	ScopedBindTexture texture_lock(sphere_texture);
	ScopedUseProgram shader_lock(shader);

	switch (object)
	{
	case Object::Teacup:
		solid_teacup(1.f);
		break;
	case Object::Teaspoon:
		solid_teaspoon(1.f);
		break;
	case Object::Teapot:
		solid_teapot(1.f);
		break;
	case Object::Model:
	default:
		model.draw();
	}
}
