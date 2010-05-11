/*
 * FrameDataEq.h
 *
 *  Created on: Sep 1, 2009
 *      Author: daniel
 */

#ifndef FRAME_DATA_EQ_HPP
#define FRAME_DATA_EQ_HPP

#include "../Common/FrameData.hpp"
#include "EqInclude.hpp"

class FrameDataEq: public FrameData, public eq::Object
{
public:
	FrameDataEq(Algorithm* algorithm_stack, MeshLoader* mesh_loader_stack) :
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

	void serialize(eq::net::DataOStream& os, const uint64_t dirty)
	{
		eq::Object::serialize(os, dirty);

		if (dirty & DIRTY_LIGHT)
			os << lights;

		if (dirty & DIRTY_MODEL)
			os << model_name;

		if (dirty & DIRTY_RALGO)
			os << ralgo_name;
	}

	void deserialize(eq::net::DataIStream& is, const uint64_t dirty)
	{
		eq::Object::deserialize(is, dirty);

		if (dirty & DIRTY_LIGHT)
			is >> lights;

		if (dirty & DIRTY_MODEL)
		{
			is >> model_name;
			FrameData::load_model(model_name);
		}

		if (dirty & DIRTY_RALGO)
		{
			is >> ralgo_name;
			FrameData::set_render_algorithm(ralgo_name);
		}
	}

private:
	enum DirtyBits
	{
		DIRTY_LIGHT = DIRTY_CUSTOM << 1,
		DIRTY_MODEL = DIRTY_CUSTOM << 2,
		DIRTY_RALGO = DIRTY_CUSTOM << 3
	};
};

#endif /* FRAME_DATA_EQ_HPP */
