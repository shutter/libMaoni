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

//! Path class
/*!
  The path class defines a container for file-path information.
*/

class Path
{
public:
    //! Creates a path object from a path as string value
    /*!
      \param path The path as a constant string reference
    */
	Path(std::string const& path);

	virtual ~Path();

	//! The file-path assignment operator
	/*!
	  \param value A const reference to a string value
	 */
	void path(std::string const& value);

	//! The file-path call operator
    /*!
      \return The file-path as const string
    */
	std::string path() const;

	//! To be implemented in subclasses for file-type constraints
	/*!
	  \return The file-type description and type-list to use in file-dialogs
			  as const char pointer. E.g. "Image files (*.jpg *.png)"
	 */
	virtual const char* const filter() const;

private:
	Path(Path const& other);
	void operator=(Path const& other);
	virtual void reset();

private:
	std::string path_;
};

#endif /* MAONI_PATH_HPP */
