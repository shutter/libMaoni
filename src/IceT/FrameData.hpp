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

#include <iostream>

class FrameDataIceT: public FrameData
{
public:
	FrameDataIceT(RenderAlgorithm* algorithm_stack,
			MeshLoader* mesh_loader_stack);
	~FrameDataIceT();

	virtual void load_model(std::string const& filename)
	{
		setModelChanged();
		FrameData::load_model(filename);
	}

	virtual void set_render_algorithm(std::string const& name)
	{
		setRendererChanged();
		FrameData::set_render_algorithm(name);
	}

	virtual Light& light(std::size_t i)
	{
		setLightChanged();
		return FrameData::light(i);
	}

	virtual const Light& light(std::size_t i) const
	{
		return FrameData::light(i);
	}

	bool master() const
	{
		return world.rank() == 0;
	}

	int myrank() const
	{
		return world.rank();
	}

	int ranks() const
	{
		return world.size();
	}

	void animate();

	void resize(int w, int h);

	virtual int getMWidth() const
	{
		return mwidth;
	}

	virtual int getMHeight() const
	{
		return mheight;
	}

	virtual void setLightChanged()
	{
		change |= LIGHT_CHANGED;
	}

	virtual void setModelChanged()
	{
		change |= MODEL_CHANGED;
	}

	virtual void setRenderParamChanged()
	{
		change |= RENDERPARAM_CHANGED;
	}

	virtual void setRendererChanged()
	{
		change |= RENDERER_CHANGED;
	}

	virtual void setTilesChanged()
	{
		change |= TILES_CHANGED;
	}

	virtual void setStrategyChanged(){
		change |= STRATEGY_CHANGED;
	}

	virtual void setStrategy(int strategy);

	virtual bool getDoResize() const
	{
		return do_resize;
	}

	virtual void setDoResize(bool flag){
		do_resize = flag;
	}

private:
	virtual void do_import_scene(boost::archive::xml_iarchive& archive);
	virtual void do_export_scene(boost::archive::xml_oarchive& archive);

private:
	boost::mpi::communicator world;
	int mwidth, mheight;

	enum change_bits
	{
		LIGHT_CHANGED = 1,
		MODEL_CHANGED = 2,
		RENDERPARAM_CHANGED = 4,
		RENDERER_CHANGED = 8,
		TILES_CHANGED = 16,
		STRATEGY_CHANGED = 32
	};

	short change;
	bool do_resize;
	int strategy_;

public:
	std::vector<Tile> tiles;
};

#endif /* MAONI_ICET_FRAMEDATA_HPP */
