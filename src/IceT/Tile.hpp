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

#ifndef MAONI_ICET_TILE_HPP
#define MAONI_ICET_TILE_HPP

#include <boost/serialization/nvp.hpp>
#include <boost/mpi/datatype.hpp>
#include <Maoni/Vector.hpp>

struct Tile
{
	Tile() :
		visible(false), fullscreen(false), x(0), y(0),
				min_box(-1.f, -1.f, -1.f), max_box(1.f, 1.f, 1.f), sx(800), //
				sy(600), render_group(0)
	{
	}

	bool visible;
	bool fullscreen;
	int x, y; // offset
	int sx, sy; // size
	int render_group;
	Vec3 min_box, max_box; //< axis aligned bounding box

	template<class Archive>
	void serialize(Archive & archive, unsigned int)
	{
		archive & BOOST_SERIALIZATION_NVP(visible);
		archive & BOOST_SERIALIZATION_NVP(fullscreen);
		archive & BOOST_SERIALIZATION_NVP(x);
		archive & BOOST_SERIALIZATION_NVP(y);
		archive & BOOST_SERIALIZATION_NVP(sx);
		archive & BOOST_SERIALIZATION_NVP(sy);
		archive & BOOST_SERIALIZATION_NVP(render_group);
		archive & BOOST_SERIALIZATION_NVP(min_box);
		archive & BOOST_SERIALIZATION_NVP(max_box);
	}
};

BOOST_IS_MPI_DATATYPE( Tile)

#endif /* MAONI_ICET_TILE_HPP */
