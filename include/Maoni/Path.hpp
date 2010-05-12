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

#ifndef MAONI_PATH_HPP
#define MAONI_PATH_HPP

#include <string>

class Path
{
public:
	Path(std::string const& path);

	virtual ~Path();

	std::string const& operator=(std::string const& other);

	operator const std::string&() const;

	virtual const char* const filter() const;

private:
	Path(Path const& other);
	void operator=(Path const& other);
	virtual void reset();

private:
	std::string path;
};

#endif /* MAONI_PATH_HPP */
