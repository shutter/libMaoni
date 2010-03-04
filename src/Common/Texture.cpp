/*
 * texture.cpp
 *
 *  Created on: 31.10.2009
 *      Author: daniel
 */

#include <GL/glew.h>
#include <Maoni/Texture.hpp>
#include <Maoni/ScopedLocks.hpp>

#include <QImage>
#include <QGLWidget>

Texture::Texture(const std::string& path) :
	path_(path), name_(0)
{
}

Texture::Texture(Texture const& other) :
	path_(other.path_), name_(0)
{
}

Texture::~Texture()
{
	reset();
}

Texture const& Texture::operator=(Texture const& other)
{
	reset();
	path_ = other.path_;
	return other;
}

std::string const& Texture::operator=(std::string const& other)
{
	reset();
	path_ = other;
	return other;
}

Texture::operator unsigned int()
{
	if (!name_)
	{
		glGenTextures(1, &name_);

		QImage image(path_.c_str());
		QImage teximage = QGLWidget::convertToGLFormat(image);

		ScopedBindTexture texture_lock(name_);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, teximage.width(), teximage.height(),
				0, GL_RGB, GL_UNSIGNED_BYTE, teximage.bits());
	}

	return name_;
}

Texture::operator const std::string&() const
{
	return path_;
}

void Texture::reset()
{
	glDeleteTextures(1, &name_);
	name_ = 0;
}
