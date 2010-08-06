/*
 *      from http://wiki.delphigl.com/index.php/shader_Bumpmapping
 */

#include <Maoni.hpp>

SHADER_SOURCE(vertex_source, (version 120),

		const int LIGHT_COUNT = 1; //Anzahl der berücksichtigten Lichter
		varying vec3 N; //NormalenVektor
		varying vec3 V; //VertexVektor
		varying vec3 lightvec[LIGHT_COUNT]; //LichtVektor(en)
		void main(void)
		{
			gl_TexCoord[0] = gl_MultiTexCoord0;
			N = normalize(gl_Normal);
			V = vec3(gl_ModelViewMatrix * gl_Vertex);
			for(int i = 0; i < LIGHT_COUNT; i++)
			{
				lightvec[i] = normalize(gl_LightSource[i].position.xyz - V);
			}
			gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
		}
);

SHADER_SOURCE(fragment_source, (version 120),

		const float PI = 3.14159265; //Pi, zur Berechnung der Rotation
		const int LIGHT_COUNT = 1; //Anzahl der berücksichtigten Lichter
		varying vec3 N; //NormalenVektor
		varying vec3 V; //VertexVektor
		varying vec3 lightvec[LIGHT_COUNT]; //LichtVektor(en)
		uniform sampler2D color_map; //normale Textur
		uniform sampler2D normal_map; //NormalMap

		//dreht einen Punkt um eine Achse im Raum
		//@a: Achse um die gedreht wird
		//@p: Punkt der gedreht werden soll
		//@rad: Winkel im BogenMaß
		vec3 rotate(vec3 a, vec3 p, float rad)
		{
			vec3 p1 = cos(rad) * p +
			sin(rad) * cross(a, p);
			return p1;
		}

		void main(void)
		{
			vec2 TexCoord = vec2(gl_TexCoord[0]); //TexturKoordinaten zwischenspeichern
			vec3 G = normalize(vec3(dFdx(TexCoord.s), dFdy(TexCoord.t), 0.0)); //Gradient berechnen
			vec3 B = normalize(rotate(N, cross(N, G), -0.25*PI)); //Bitangente berechnen
			vec3 T = normalize(cross(B, N)); //Tangente berechnen
			mat3 M = mat3(T, B, N); //Werte zu Matrix zusammensetzen

			//normale aus den NormalMapDaten und den Matricen errechnen
			vec3 normal = normalize((vec3(texture2D(normal_map, TexCoord)) - vec3(0.5, 0.5, 0.5)) * M);
			normal = gl_NormalMatrix * normal;

			//Normale Lichtberechnung aus dem Per-Pixel-light-Shader
			vec3 Eye = normalize(-V);
			vec4 EndColor = vec4(0.0, 0.0, 0.0, 0.0);
			for(int i = 0; i < LIGHT_COUNT; i++)
			{
				vec3 Reflected = normalize(reflect(-lightvec[i], normal));
				vec4 IAmbient = gl_LightSource[i].ambient * gl_FrontMaterial.ambient;
				vec4 IDiffuse = gl_LightSource[i].diffuse * gl_FrontMaterial.diffuse *
				max(dot(normal, lightvec[i]), 0.0);
				vec4 ISpecular = gl_LightSource[i].specular * gl_FrontMaterial.specular *
				pow( max( dot(Reflected, Eye), 0.0), gl_FrontMaterial.shininess);
				EndColor += (IAmbient+IDiffuse+ISpecular);
			}
			EndColor += gl_FrontMaterial.emission;

			gl_FragColor = (gl_FrontLightModelProduct.sceneColor + EndColor) * texture2D(color_map, TexCoord);
		}
);

SHADER_PROGRAM(DGLBumpMappingShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(DGLBumpMapping,
		(ShaderProgram, shader, DGLBumpMappingShader())
		(Texture, color_texture, "../examples/Models/dgl_color_map.jpg")
		(Texture, normal_texture, "../examples/Models/dgl_normal_map.jpg")
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
	ScopedEnable normal_map_2D_lock(GL_TEXTURE_2D);
	ScopedBindTexture normal_map_lock(normal_texture, GL_TEXTURE0);
	ScopedEnable color_map_2D_lock(GL_TEXTURE_2D);
	ScopedBindTexture color_map_lock(color_texture, GL_TEXTURE1);
	ScopedUseProgram shader_lock(shader);

	glUniform1i(glGetUniformLocation(shader, "normal_map"), 0);
	glUniform1i(glGetUniformLocation(shader, "color_map"), 1);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	// Top Left Of The Texture and Quad
	glEnd();
}
