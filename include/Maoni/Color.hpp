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

#ifndef MAONI_COLOR_HPP
#define MAONI_COLOR_HPP

//! Color class
/*!
  The color class is used to exchange color information from GUI or loader
  to algorithms to the OpenGL state machine. It consists of arithmetic (0.f to 1.f) RGBA values
*/

class Color
{
public:
    //! Creates a color object from scratch initialized by 1.0f
	Color()
	{
		impl[0] = impl[1] = impl[2] = impl[3] = 1.f;
	}

    //! Creates a color object from another color object reference
    /*!
      \param other a color reference argument.
    */
	Color(Color const& other)
	{
		impl[0] = other.red();
		impl[1] = other.green();
		impl[2] = other.blue();
		impl[3] = other.alpha();
	}

    //! Creates a color object from RGBA values
    /*!
      \param red a float argument.
      \param green a float argument.
      \param blue a float argument.
      \param alpha a float argument.
    */
	Color(float red, float green, float blue, float alpha)
	{
		impl[0] = red;
		impl[1] = green;
		impl[2] = blue;
		impl[3] = alpha;
	}

    //! The red value getter
    /*!
      \return The arithmetic red color value
    */
	float red() const
	{
		return impl[0];
	}

    //! The green value getter
    /*!
      \return The arithmetic green color value
    */
	float green() const
	{
		return impl[1];
	}

    //! The blue value getter
    /*!
      \return The arithmetic blue color value
    */
	float blue() const
	{
		return impl[2];
	}

    //! The alpha value getter
    /*!
      \return The arithmetic alpha opacity value
    */
	float alpha() const
	{
		return impl[3];
	}

	//! Make the color implicity return a pointer to its RGBA float array
    /*!
      \return The arithmetic RGBA float array pointer
    */
	operator const float*() const
	{
		return impl;
	}

private:
	float impl[4];
};

#endif /* MAONI_COLOR_HPP */
