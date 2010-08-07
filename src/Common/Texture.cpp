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

#include <Maoni/glew.h>
#include <Maoni/Texture.hpp>
#include <Maoni/ScopedLocks.hpp>

#include <QImage>
#include <QGLWidget>

Texture::Texture(const std::string& path) :
	Path(path), name(0)
{
}

Texture::operator unsigned int() const
{
	if (!name)
	{
		glGenTextures(1, &name);

		QImage image(path().c_str());
		QImage teximage = QGLWidget::convertToGLFormat(image);
		ScopedBindTexture texture_lock(name);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, teximage.width(), teximage.height(), 0, GL_RGBA,
				GL_UNSIGNED_BYTE, teximage.bits());
	}

	return name;
}

void Texture::reset()
{
	glDeleteTextures(1, &name);
	name = 0;
}

const char* const Texture::filter() const
{
	return "Image files (*.jpg *.png)";
}
