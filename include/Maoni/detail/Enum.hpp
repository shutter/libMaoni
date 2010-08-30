/*
 * libMaoni - common viewing framework
 *
 * Copyright (C) 2009, 2010 Daniel Pfeifer
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

#ifndef MAONI_DETAIL_ENUM_HPP
#define MAONI_DETAIL_ENUM_HPP

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>

#define COMMA_SEP_STRINGS(r, data, elem) BOOST_PP_STRINGIZE(elem),             \

class Enum
{
public:
	Enum(int v) :
		value(v)
	{
	}

	operator int() const
	{
		return value;
	}

	virtual int size() const
	{
		return 0;
	}

	virtual const char* const * names() const
	{
		return 0;
	}

private:
	int value;
};

#endif /* MAONI_DETAIL_ENUM_HPP */
