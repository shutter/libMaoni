/*
 * Copyright (c) 2010 Daniel Pfeifer, University of Zurich
 */

#include <Maoni/glew.h>
#include "Teaset.h"
#include "TeasetData.h"

/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

static void _bezier_patch(
		GLint grid,
		GLenum type,
		int num,
		float(*vertices)[3],
		int(*patches)[16])
{
	float p[16][3];
	int i, k, l;

	glPushAttrib(GL_ENABLE_BIT | GL_EVAL_BIT);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	for (i = 0; i < num; ++i)
	{
		for (k = 0; k < 16; ++k)
		{
			for (l = 0; l < 3; ++l)
				p[k][l] = vertices[patches[i][k]][l];
		}

		glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.f, 1.f, 2, 2, 0.f, 1.f, 4, 2,
				&tex[0][0][0]);
		glMap2f(GL_MAP2_VERTEX_3, 0.f, 1.f, 3, 4, 0.f, 1.f, 12, 4, &p[0][0]);
		glMapGrid2f(grid, 0.f, 1.f, grid, 0.f, 1.f);
		glEvalMesh2(type, 0, grid, 0, grid);
	}

	glPopAttrib();
}

static void _teacup(GLint grid, GLfloat scale, GLenum type)
{
	glPushMatrix();
	glRotatef(180.f, 0.f, 1.f, 0.f);
	glScalef(1.2f * scale, 1.2f * scale, 1.2f * scale);
	glTranslatef(0.f, -0.5f, 0.0f);

	_bezier_patch(grid, type, 16, teacup_vertices, teacup_patches);

	glPopMatrix();
}

static void _teapot(GLint grid, GLfloat scale, GLenum type)
{
	glPushMatrix();
	glRotatef(270.f, 1.f, 0.f, 0.f);
	glScalef(0.4f * scale, 0.4f * scale, 0.4f * scale);
	glTranslatef(0.f, 0.f, -1.5f);

	_bezier_patch(grid, type, 32, teapot_vertices, teapot_patches);

	glPopMatrix();
}

static void _teaspoon(GLint grid, GLfloat scale, GLenum type)
{
	glPushMatrix();
	glRotatef(90.f, 0.f, 0.f, 1.f);
	glRotatef(90.f, 0.f, 1.f, 0.f);
	glScalef(2.f * scale, 2.f * scale, 2.f * scale);
	glTranslatef(0.0f, 0.4f, 0.f);

	_bezier_patch(grid, type, 16, teaspoon_vertices, teaspoon_patches);

	glPopMatrix();
}

/* -- INTERFACE FUNCTIONS -------------------------------------------------- */

//! Renders a beautiful wired teacup...
void wire_teacup(GLfloat size)
{
	_teacup(10, size, GL_LINE);
}

//! Renders a beautiful filled teacup...
void solid_teacup(GLfloat size)
{
	_teacup(7, size, GL_FILL);
}

//! Renders a beautiful wired teapot...
void wire_teapot(GLfloat size)
{
	_teapot(10, size, GL_LINE);
}

//! Renders the famous teacupahedron...
void solid_teapot(GLfloat size)
{
	_teapot(7, size, GL_FILL);
}

//! Renders a beautiful wired teaspoon...
void wire_teaspoon(GLfloat size)
{
	_teaspoon(10, size, GL_LINE);
}

//! Renders a beautiful filled teaspoon...
void solid_teaspoon(GLfloat size)
{
	_teaspoon(7, size, GL_FILL);
}
