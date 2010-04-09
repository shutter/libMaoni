/*
 * FrameDataEq.h
 *
 *  Created on: Sep 1, 2009
 *      Author: daniel
 */

#ifndef FRAME_DATA_EQ_HPP
#define FRAME_DATA_EQ_HPP

#include "../Common/FrameData.hpp"
#include <eq/client/object.h>
#include <eq/net/dataIStream.h>
#include <eq/net/dataOStream.h>

class FrameDataEq: public FrameData, public eq::Object
{
public:
	FrameDataEq()
	{
	}

	~FrameDataEq()
	{
	}

	bool load_model(const char* filename)
	{
		model_filename_ = filename;
		setDirty(DIRTY_MODEL);
		return FrameData::load_model(filename);
	}

	// the non-const function has to set the dirty bit
	std::vector<Light>& lights()
	{
		setDirty(DIRTY_LIGHT);
		return FrameData::lights();
	}

	using FrameData::render_algorithm;

	void render_algorithm(Algorithm::Ptr algo)
	{
		FrameData::render_algorithm(algo);
		this->setDirty(DIRTY_RALGO);
	}

	void mouse_event()
	{
		setDirty(DIRTY_MOUSE);
	}

	void serialize(eq::net::DataOStream& os, const uint64_t dirty)
	{
		eq::Object::serialize(os, dirty);

		if (dirty & DIRTY_LIGHT)
			os << lights_;

		if (dirty & DIRTY_MODEL)
			os << model_filename_;

		if (dirty & DIRTY_RALGO)
		{
			if (render_algorithm_)
				os << std::string(render_algorithm_->name());
			else
				os << std::string("NO ALGORITHM SET");
		}

		if (dirty & DIRTY_MOUSE)
			os << curquat[0] << curquat[1] << curquat[2] << curquat[3]
					<< translation.x() << translation.y() << translation.z();
	}

	void deserialize(eq::net::DataIStream& is, const uint64_t dirty)
	{
		eq::Object::deserialize(is, dirty);

		if (dirty & DIRTY_LIGHT)
			is >> lights_;

		if (dirty & DIRTY_MODEL)
		{
			is >> model_filename_;
			if (!model_filename_.empty())
				FrameData::load_model(model_filename_.c_str());
		}

		if (dirty & DIRTY_RALGO)
		{
			std::string name;
			is >> name;

			std::cout << "TODO: load render algorithm " << name << std::endl;

			// render_algorithm_ = Algorithm::get_by_name(name);
		}

		if (dirty & DIRTY_MOUSE)
		{
			is >> curquat[0] >> curquat[1] >> curquat[2] >> curquat[3]
					>> translation.x() >> translation.y() >> translation.z();
		}
	}

private:
	enum DirtyBits
	{
		DIRTY_LIGHT = DIRTY_CUSTOM << 1,
		DIRTY_MODEL = DIRTY_CUSTOM << 2,
		DIRTY_RALGO = DIRTY_CUSTOM << 3,
		DIRTY_MOUSE = DIRTY_CUSTOM << 4
	};

	std::string model_filename_;
};

#endif /* FRAME_DATA_EQ_HPP */
