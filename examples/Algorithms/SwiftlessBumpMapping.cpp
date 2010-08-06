/*
 *      from http://www.swiftless.com/tutorials/glsl/8_bump_mapping.html
 */

#include <Maoni.hpp>

SHADER_SOURCE(vertex_source, (version 120),

		void main() {
		gl_TexCoord[0] = gl_MultiTexCoord0;

		// Set the position of the current vertex
		gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
		}
);

SHADER_SOURCE(fragment_source, (version 120),

		uniform sampler2D color_map;
		uniform sampler2D normal_map;

		void main() {

		// Extract the normal from the normal map
		vec3 normal = normalize(texture2D(normal_map, gl_TexCoord[0].st).rgb * 2.0 - 1.0);

		// Determine where the light is positioned (this can be set however you like)
		vec3 light_pos = normalize(vec3(1.0, 1.0, 1.5));
		// vec3 light_pos = normalize(gl_LightSource[0].position.xyz);


		// Calculate the lighting diffuse value
		float diffuse = max(dot(normal, light_pos), 0.0);

		vec3 color = diffuse * texture2D(color_map, gl_TexCoord[0].st).rgb;

		// Set the output color of our current pixel
		gl_FragColor = vec4(color, 1.0);
		}
);

SHADER_PROGRAM(SwiftlessBumpMappingShader,
	(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(SwiftlessBumpMapping,
	(ShaderProgram, shader, SwiftlessBumpMappingShader())
	(Texture, color_texture, "../examples/Models/ozone_color_map.jpg")
	(Texture, normal_texture, "../examples/Models/ozone_normal_map.jpg")
	(Color, ambient, Color(0.6, 0.6, 0.6, 1.0))
	(Color, diffuse, Color(0.8, 0.8, 0.8, 1.0))
	(Color, specular, Color(0.6, 0.6, 0.6, 0.0))
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
	ScopedEnable color_map_2D_lock(GL_TEXTURE_2D);
	ScopedBindTexture color_map_lock(color_texture, GL_TEXTURE0);
	ScopedEnable normal_map_2D_lock(GL_TEXTURE_2D);
	ScopedBindTexture normal_map_lock(normal_texture, GL_TEXTURE1);
	ScopedUseProgram shader_lock(shader);

	glUniform1i(glGetUniformLocation(shader, "color_map"), 0);
	glUniform1i(glGetUniformLocation(shader, "normal_map"), 1);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	// Top Left Of The Texture and Quad
		glColor3f(1.f, 1.f, 1.f);
	glEnd();
}

