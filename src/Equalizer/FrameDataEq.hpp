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

#ifndef FRAME_DATA_EQ_HPP
#define FRAME_DATA_EQ_HPP

#include "../Common/FrameData.hpp"
#include "EqInclude.hpp"

class FrameDataEq: public FrameData, public eq::Object
{
public:
	FrameDataEq(RenderAlgorithm* algorithm_stack, MeshLoader* mesh_loader_stack) :
		FrameData(algorithm_stack, mesh_loader_stack)
	{
	}

	FrameDataEq(FrameDataEq const& other) :
		FrameData(other)
	{
	}

	virtual void load_model(const char* filename)
	{
		setDirty(DIRTY_MODEL);
		FrameData::load_model(filename);
	}

	virtual void set_render_algorithm(std::string const& name)
	{
		setDirty(DIRTY_RALGO);
		FrameData::set_render_algorithm(name);
	}

	virtual Light& light(std::size_t i)
	{
		setDirty(DIRTY_LIGHT);
		return FrameData::light(i);
	}

	void serialize(eq::net::DataOStream& os, const uint64_t dirty);

	void deserialize(eq::net::DataIStream& is, const uint64_t dirty);

private:
	enum DirtyBits
	{
		DIRTY_LIGHT = DIRTY_CUSTOM << 1,
		DIRTY_MODEL = DIRTY_CUSTOM << 2,
		DIRTY_RALGO = DIRTY_CUSTOM << 3,
		DIRTY_RENDERER = DIRTY_CUSTOM << 4
	};
};

#endif /* FRAME_DATA_EQ_HPP */
