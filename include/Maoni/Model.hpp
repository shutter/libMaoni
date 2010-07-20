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

#ifndef MAONI_MODEL_HPP
#define MAONI_MODEL_HPP

#include <boost/scoped_ptr.hpp>

//! The model class
/*!
 The abstract model class defines the minimal function set for a
 model class.
 */

class Model
{
public:
	typedef boost::scoped_ptr<Model> Ptr;

	//! Create an empty model
	Model()
	{
	}

	//! Draw the model
	virtual void draw() const
	{
	}

private:
	Model(Model const&);
	void operator=(Model const&);
};

#endif /* MAONI_MODEL_HPP */
