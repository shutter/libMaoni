/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Logo.hpp"
#include <GL/glew.h>
#include <iostream>

void Logo::draw() const
{
	if (!render)
		return;

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);
	glColor4f(1.f, 1.f, 1.f, 1.f);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(pos_x1, pos_y2); // Bottom left of the texture and quad
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(pos_x2, pos_y2); // Bottom right of the texture and quad
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(pos_x2, pos_y1); // Top right of the texture and quad
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(pos_x1, pos_y1); // Top left of the texture and quad
	}
	glEnd();

	glColor4fv(color);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void Logo::calc_pos(int window_width, int window_height)
{
	this->window_width = window_width;
	this->window_height = window_height;

	GLint width = 0, height = 0;
	glBindTexture(GL_TEXTURE_2D, texture);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (width == 0 || height == 0)
	{
		std::cout << "Could not load logo!";
		pos_x1 = 0;
		pos_x2 = 0;
		pos_y1 = 0;
		pos_y2 = 0;
	}
	else
	{
		pos_x2 = (int)(window_width * 0.98);
		pos_y2 = window_height - (window_width - pos_x2);
		pos_x1 = (int)(window_width * 0.76);
		pos_y1 = pos_y2 - (int)(((pos_x2 - pos_x1) / float(width)) * height);

//		std::cout << "Logo loaded - tw: " << width << " th: " << height
//		 << " ww: " << window_width << " wh: " << window_height
//		 << " x1: " << pos_x1 << " x2: " << pos_x2 << " y1: "
//		 << pos_y1 << " y2: " << pos_y2 << std::endl;
	}
}
