/*
 * A Brick Shader from the "OrangeBook": OpenGL Shading Language, 3rd Edition
 * By Randi J. Rost, Dan Ginsburg, John M. Kessenich, Bill Licea-Kane, Barthold Lichtenbelt, Hugh Malan, Mike Weiblen
 * Downgraded to GLSL 1.20
 */

#include <Maoni.hpp>
#include "../Loaders/VBOModel.hpp"
#include <boost/la/all.hpp>
using namespace boost::la;

SHADER_SOURCE(vertex_source, (version 120),

		const float SpecularContribution = 0.3;
		const float DiffuseContribution = 1.0 - SpecularContribution;

		varying float LightIntensity;
		varying vec2 MCposition;

		void main()
		{
			vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
			vec3 tnorm = normalize(gl_NormalMatrix * gl_Normal);
			vec3 lightVec = normalize((gl_LightSource[0].position).xyz - ecPosition);
			vec3 reflectVec = reflect(-lightVec, tnorm);
			vec3 viewVec = normalize(-ecPosition);
			float diffuse = max(dot(lightVec, tnorm), 0.0);
			float spec = 0.0;

			if (diffuse > 0.0)
			{
				spec = max(dot(reflectVec, viewVec), 0.0);
				spec = pow(spec, 16.0);
			}

			LightIntensity = DiffuseContribution * diffuse +
			SpecularContribution * spec;
			MCposition = gl_Vertex.xy;
			gl_Position = ftransform();
		}
);

SHADER_SOURCE(fragment_source, (version 120),

		uniform vec3 BrickColor;
		uniform vec3 MortarColor;
		uniform vec2 BrickSize;
		uniform vec2 BrickPct;

		varying float LightIntensity;
		varying vec2 MCposition;

		void main()
		{
			vec3 color;
			vec2 position;
			vec2 useBrick;

			position = MCposition / BrickSize;

			if (fract(position.y * 0.5) > 0.5)
			position.x += 0.5;

			position = fract(position);

			useBrick = step(position, BrickPct);

			color = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);
			color *= LightIntensity;
			gl_FragColor = vec4(color, 1.0);
		}
);

SHADER_PROGRAM(BrickShader,
		(VERTEX, vertex_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(Brick,
		(ShaderProgram, shader, BrickShader())
		(Color, brick_color, Color(1.0, 0.3, 0.2, 1.0))
		(Color, mortal_color, Color(0.85, 0.86, 0.84, 1.0))
		(Vec2, brick_size, Vec2(0.3, 0.15))
		(Vec2, brick_pct, Vec2(0.9, 0.85))
)
{
	ScopedUseProgram shader_lock(shader);

	GLint loc_brick_color = glGetUniformLocation(shader, "BrickColor");
	GLint loc_mortal_color = glGetUniformLocation(shader, "MortarColor");
	glUniform3f(loc_brick_color, brick_color.red(), brick_color.green(),
			brick_color.blue());
	glUniform3f(loc_mortal_color, mortal_color.red(), mortal_color.green(),
			mortal_color.blue());

	GLint loc_brick_size = glGetUniformLocation(shader, "BrickSize");
	GLint loc_brick_pct = glGetUniformLocation(shader, "BrickPct");
	glUniform2f(loc_brick_size, brick_size.data[0], brick_size.data[1]);
	glUniform2f(loc_brick_pct, brick_pct.data[0], brick_pct.data[1]);

	model.draw();
}
