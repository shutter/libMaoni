/*
 * A blinn phong illumination shader
 */

#include <GL/glew.h>
#include <Maoni.hpp>

SHADER_SOURCE(vertex_source, (version 120),
		/*
		 * Vertex shader for Phong/Blinn-Phong Shading with one light source.
		 * Copyright (c) 2007, Tobias Wolf <twolf@access.unizh.ch>
		 */

		varying vec3 normalEye;
		varying vec4 positionEye;

		void main()
		{
			// transform normal to eye coordinates
			normalEye = normalize(gl_NormalMatrix * gl_Normal);

			// transform position to eye coordinates
			positionEye = normalize(gl_ModelViewMatrix * gl_Vertex);

			// transform position to screen coordinates
			//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
			gl_Position = ftransform();

			// pass the vertex colors on to the fragment shader
			gl_FrontColor = gl_Color;
		}
);

SHADER_SOURCE(fragment_source, (version 120),
		/*
		 * Fragment shader for Phong/Blinn-Phong Shading with one light source.
		 *  Copyright (c) 2007, Tobias Wolf <twolf@access.unizh.ch>
		 */

		varying vec3 normalEye;
		varying vec4 positionEye;

		void main()
		{
			// normalize interpolated normal, compute view vector from position
			vec3 normal = normalize(normalEye);
			vec3 view = normalize(-positionEye).xyz;

			// compute light vector
			vec3 light;
			if (gl_LightSource[0].position.w == 0.0)
			{
				// directional light
				light = normalize(gl_LightSource[0].position).xyz;
			}
			else
			{
				// point light
				light = normalize(gl_LightSource[0].position - positionEye).xyz;
			}

			// compute the ambient component
			//vec4 ambient = gl_FrontLightProduct[0].ambient;
			vec4 ambient = gl_LightSource[0].ambient * gl_Color;

			// compute the diffuse component
			float dotLN = dot(light, normal);
			//vec4 diffuse = gl_FrontLightProduct[0].diffuse * max( dotLN, 0.0 );
			vec4 diffuse = gl_LightSource[0].diffuse * gl_Color * max(dotLN, 0.0);

			// compute the specular component
			float factor;
			if (dotLN > 0.0)
			{
				factor = 1.0;
			}
			else
			{
				factor = 0.0;
			}

			// pure Phong
			//vec3 reflect = normalize( reflect( -light, normal ) );
			//vec4 specular =
			//    gl_FrontLightProduct[0].specular * factor *
			//    max( pow( dot( reflect, view ), gl_FrontMaterial.shininess ), 0.0 );

			// modified Blinn-Phong
			vec3 halfway = normalize(light + view);
			vec4 specular = gl_FrontLightProduct[0].specular * factor * max(pow(dot(
									normal, halfway), gl_FrontMaterial.shininess), 0.0);

			// sum the components up, defaulting alpha to 1.0
			gl_FragColor = vec4(vec3(gl_FrontLightModelProduct.sceneColor + ambient
							+ diffuse + specular), 1.0);
		}
);

SHADER_PROGRAM(BlinnPhongShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(BlinnPhong,
		(bool, wired, false)
		(bool, bounding_sphere, false)
		(ShaderProgram, shader, BlinnPhongShader())
		(Color, ambient, Color(0.24725, 0.1995, 0.0745, 1.0))
		(Color, diffuse, Color(0.75164, 0.60648, 0.22648, 1.0))
		(Color, specular, Color(0.628281, 0.555802, 0.366065, 0.0))
		(float, shininess, 51.2))
{
	ScopedUseProgram shader_lock(shader);

	ScopedEnable color_material_lock(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	model.draw();

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
