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

#ifndef VMMVIEW_DETAIL_SCOPED_LOCKS_HPP
#define VMMVIEW_DETAIL_SCOPED_LOCKS_HPP

#include <Maoni/glew.h>

namespace detail
{

//! The ScopedEnable class
/*!
  Parent of ScopeEnable and ScopeDisable to having not to implement the
  Dtor twice
*/
class ScopedEnable
{
protected:
	//! Creates a ScopedEnable object for a certain OpenGL state parameter
	ScopedEnable(GLenum cap) :
		cap_(cap), enabled_(!!glIsEnabled(cap))
	{
	}

public:
	/*!
	  Resets the OpenGL state which was changed in an RenderAlgorithm
	  to the one it had before
	 */
	~ScopedEnable()
	{
		if (enabled_)
			glEnable(cap_);
		else
			glDisable(cap_);
	}

private:
	GLenum cap_;
	bool enabled_;
};

} // namespace detail

#endif /* VMMVIEW_DETAIL_SCOPED_LOCKS_HPP */
