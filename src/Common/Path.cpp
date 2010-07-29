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

#include <Maoni/Path.hpp>

Path::Path(const std::string& path) :
	path_(path)
{
}

Path::~Path()
{
}

void Path::path(std::string const& other)
{
	if (path_ != other)
	{
		this->reset();
		path_ = other;
	}
}

std::string Path::path() const
{
	return path_;
}

const char* const Path::filter() const
{
	return 0;
}

void Path::reset()
{
}
