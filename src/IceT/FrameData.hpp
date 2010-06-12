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

#ifndef MAONI_ICET_FRAMEDATA_HPP
#define MAONI_ICET_FRAMEDATA_HPP

#include "../Common/FrameData.hpp"
#include <boost/mpi/communicator.hpp>
#include "Tile.hpp"

class FrameDataIceT: public FrameData
{
public:
	FrameDataIceT(Algorithm* algorithm_stack, MeshLoader* mesh_loader_stack);
	~FrameDataIceT();

	bool master() const
	{
		return world.rank() == 0;
	}

	int rank() const
	{
		return world.rank();
	}

	void animate();

private:
	boost::mpi::communicator world;
public:
	std::vector<Tile> tiles;
};

#endif /* MAONI_ICET_FRAMEDATA_HPP */
