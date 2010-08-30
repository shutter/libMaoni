/*
 * libMaoni - common viewing framework
 *
 * Copyright (C) 2009, 2010 Daniel Pfeifer, Stefan Hutter
 * Visualization and Multimedia Lab, University of Zurich
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

#ifndef MAONI_TEXTURE_HPP
#define MAONI_TEXTURE_HPP

#include <Maoni/Path.hpp>

//! Texture class
/*!
 The texture class is used to store file-path information of jpg or png
 pictures, which can be loaded as OpenGL texture in a render algorithm.
 */
class Texture: public Path
{
public:
	//! Constructs a texture object from a path as string value
	/*!
	 \param path The path as a constant string reference
	 */
	Texture(std::string const& path);

	//! Make the texture implicitly return the glTexture value
	/*!
	 \return The OpenGL handle of this texture
	 */
	operator unsigned int() const;

private:
	void reset();
	const char* const filter() const;

private:
	mutable unsigned int name;
};

#endif /* MAONI_TEXTURE_HPP */
