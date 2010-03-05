/*
 * NormalDebug.cpp
 *
 *  Created on: 5 Mar 2010
 *      Author: stefan
 *
 *      from http://wiki.delphigl.com/index.php/shader_normal_debug
 */

#include <GL/glew.h>
#include <Maoni/RenderAlgorithm.hpp>
#include <Maoni/ShaderProgram.hpp>
#include <Maoni/ScopedLocks.hpp>

SHADER_SOURCE(vertex_source,
		varying vec4 V;
		varying vec3 N;

		void main()
		{
			V = gl_Vertex;
			N = gl_Normal;

			gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
		}
);

SHADER_SOURCE(geometry_source,

		varying in vec4 V[3];
		varying in vec3 N[3];

		uniform float nLength;

		void createNormal( vec3 V, vec3 N )
		{
		    gl_Position = gl_ModelViewProjectionMatrix * vec4( V, 1.0f );
		    EmitVertex();

		    gl_Position = gl_ModelViewProjectionMatrix * vec4( V + N * nLength, 1.0f );
		    EmitVertex();

		    EndPrimitive();
		}


		void main()
		{
		    for ( int i = 0; i < 3; ++i )
		    {
		        createNormal( V[i].xyz, N[i] );
		    }
		}
);

SHADER_SOURCE(fragment_source,

		void main()
		{
			gl_FragColor = vec4( 1.0, 1.0, 0.0, 1.0 );

		}
);

SHADER_PROGRAM(NormalDebugShader,
		(VERTEX, vertex_source)(GEOMETRY, geometry_source)(FRAGMENT, fragment_source),
);

RENDER_ALGORITHM(NormalDebug,
		(bool, wired, false)
		(Color, normal_color, Color(1.0, 1.0, 0.0, 1.0))
		(ShaderProgram, shader, NormalDebugShader()))
{
	ScopedUseProgram shader_lock(shader);

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//gl_FragColor = normal_color;
	model.draw();

	if (wired)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
