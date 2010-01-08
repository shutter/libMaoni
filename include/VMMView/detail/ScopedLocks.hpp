/*
 * scoped_locks.hpp
 *
 *  Created on: 01.11.2009
 *      Author: Daniel Pfeifer
 */

#ifndef VMMVIEW_DETAIL_SCOPED_LOCKS_HPP
#define VMMVIEW_DETAIL_SCOPED_LOCKS_HPP

#include <GL/gl.h>

namespace detail
{

class ScopedEnable
{
protected:
	ScopedEnable(GLenum cap) :
		cap_(cap), enabled_(glIsEnabled(cap))
	{
	}

public:
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
