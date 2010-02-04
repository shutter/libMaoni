/*
 * texture.cpp
 *
 *  Created on: 31.10.2009
 *      Author: daniel
 */

//#include <windows.h>
#include <Maoni/Texture.hpp>
#include <Maoni/ScopedLocks.hpp>

#include <QImage>
#include <QGLWidget>

void Texture::load()
{
	QImage image(path_.c_str());
	QImage teximage = QGLWidget::convertToGLFormat(image);

	ScopedBindTexture texture_lock(name_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, teximage.width(), teximage.height(), 0,
			GL_RGB, GL_UNSIGNED_BYTE, teximage.bits());
}
