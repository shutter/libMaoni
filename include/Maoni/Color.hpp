/*
 * Color.hpp
 *
 *  Created on: 08.12.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_COLOR_HPP
#define VMMVIEW_COLOR_HPP

class Color
{
public:
	Color()
	{
		impl[0] = impl[1] = impl[2] = impl[3] = 1.f;
	}

	Color(Color const& other)
	{
		impl[0] = other.red();
		impl[1] = other.green();
		impl[2] = other.blue();
		impl[3] = other.alpha();
	}

	Color(float red, float green, float blue, float alpha)
	{
		impl[0] = red;
		impl[1] = green;
		impl[2] = blue;
		impl[3] = alpha;
	}

	float red() const
	{
		return impl[0];
	}

	float green() const
	{
		return impl[1];
	}

	float blue() const
	{
		return impl[2];
	}

	float alpha() const
	{
		return impl[3];
	}

	operator const float*() const
	{
		return impl;
	}

private:
	float impl[4];
};

#endif /* VMMVIEW_COLOR_HPP */
