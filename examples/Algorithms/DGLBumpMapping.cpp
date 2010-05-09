/*
 * DGLBumpMapping.cpp
 *
 *  Created on: 5 Mar 2010
 *      Author: stefan
 *
 *      from http://wiki.delphigl.com/index.php/shader_Bumpmapping
 */

#include <GL/glew.h>
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
		uniform sampler2D Texture0; //normale Textur
		uniform sampler2D Texture1; //NormalMap

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
			vec3 normal = normalize((vec3(texture2D(Texture1, TexCoord)) - vec3(0.5, 0.5, 0.5)) * M);
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

			gl_FragColor = (gl_FrontLightModelProduct.sceneColor + EndColor) * texture2D(Texture0, TexCoord);
		}
);

SHADER_PROGRAM(DGLBumpMappingShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(DGLBumpMapping,
		(ShaderProgram, shader, DGLBumpMappingShader())
		(Texture, bump_texture, "./Models/shader_diffuse_bumpmapping_cg_texture.jpg")
		(Texture, normal_texture, "./Models/shader_diffuse_bumpmapping_cg_normal.jpg")
		(Color, ambient, Color(0.24725, 0.1995, 0.0745, 1.0))
		(Color, diffuse, Color(0.75164, 0.60648, 0.22648, 1.0))
		(Color, specular, Color(0.628281, 0.555802, 0.366065, 0.0))
		(Color, emission, Color(0.0, 0.0, 0.0, 0.0))
		(float, shininess, 51.2)
)
{
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);

	ScopedDisable lighting_lock(GL_LIGHTING);
	ScopedEnable texture_2D_lock(GL_TEXTURE_2D);
	ScopedUseProgram shader_lock(shader);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal_texture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, bump_texture);

	model.draw();
}
