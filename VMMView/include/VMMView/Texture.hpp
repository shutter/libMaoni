/*
 * texture.hpp
 *
 *  Created on: 31.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_TEXTURE_HPP
#define VMMVIEW_TEXTURE_HPP

#include <GL/gl.h>
#include <boost/noncopyable.hpp>
#include <string>
#include <iostream>

class Texture: private boost::noncopyable
{
public:
	Texture(const std::string& path) :
		path_(path)
	{
		glGenTextures(1, &name_);
		load();
	}

	~Texture()
	{
		glDeleteTextures(1, &name_);
	}

	operator GLuint() const
	{
		return name_;
	}

	operator const std::string&() const
	{
		return path_;
	}

	const std::string& operator=(const std::string& path)
	{
		path_ = path;
		load();
		return path_;
	}

private:
	void load();

	std::string path_;
	GLuint name_;
};

#endif /* VMMVIEW_TEXTURE_HPP */
