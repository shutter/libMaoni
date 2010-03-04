/*
 * texture.hpp
 *
 *  Created on: 31.10.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_TEXTURE_HPP
#define VMMVIEW_TEXTURE_HPP

#include <string>

class Texture
{
public:
	Texture(std::string const& path);

	Texture(Texture const& other);

	~Texture();

	Texture const& operator=(Texture const& other);

	std::string const& operator=(std::string const& other);

	operator unsigned int();

	operator const std::string&() const;

	void reset();

private:
	std::string path_;
	unsigned int name_;
};

#endif /* VMMVIEW_TEXTURE_HPP */
