/*
 *      from http://www.ozone3d.net/tutorials/bump_mapping.php
 */

#include <Maoni.hpp>

SHADER_SOURCE(vertex_source, (version 120),

	varying vec3 lightVec;
	varying vec3 eyeVec;
	varying vec2 texCoord;
	attribute vec3 vTangent;

	void main()
	{
		gl_Position = ftransform();
		texCoord = gl_MultiTexCoord0.xy;

		vec3 n = normalize(gl_NormalMatrix * gl_Normal);
		vec3 t = normalize(gl_NormalMatrix * vTangent);
		vec3 b = cross(n, t);

		vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
		vec3 tmpVec = gl_LightSource[0].position.xyz - vVertex;

		lightVec.x = dot(tmpVec, t);
		lightVec.y = dot(tmpVec, b);
		lightVec.z = dot(tmpVec, n);

		tmpVec = -vVertex;
		eyeVec.x = dot(tmpVec, t);
		eyeVec.y = dot(tmpVec, b);
		eyeVec.z = dot(tmpVec, n);
	}
);

SHADER_SOURCE(fragment_source, (version 120),

	varying vec3 lightVec;
	varying vec3 eyeVec;
	varying vec2 texCoord;
	uniform float invRadius;

	uniform sampler2D color_map;
	uniform sampler2D normal_map;

	void main()
	{
		float distSqr = dot(lightVec, lightVec);

		float att = clamp(1.0 - invRadius * sqrt(distSqr), 0.0, 1.0);

		vec3 lVec = lightVec * inversesqrt(distSqr);

		vec3 vVec = normalize(eyeVec);

		vec4 base = texture2D(color_map, texCoord);

		vec3 bump = normalize( texture2D(normal_map, texCoord).xyz * 2.0 - 1.0);

		vec4 vAmbient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

		float diffuse = max( dot(lVec, bump), 0.0 );

		vec4 vDiffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse *
						diffuse;

		float specular = pow(clamp(dot(reflect(-lVec, bump), vVec), 0.0, 1.0),
		                 gl_FrontMaterial.shininess );

		vec4 vSpecular = gl_LightSource[0].specular * gl_FrontMaterial.specular *
							 specular;

		gl_FragColor = ( vAmbient*base +
							 vDiffuse*base +
							 vSpecular) * att;

	}
);

SHADER_PROGRAM(OzoneBumpMappingShader,
	(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(OzoneBumpMapping,
	(ShaderProgram, shader, OzoneBumpMappingShader())
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
	glEnd();
}

