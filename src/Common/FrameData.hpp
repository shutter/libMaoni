/*
 * GlobalConfigParameter.hpp
 *
 *  Created on: 4 Aug 2009
 *      Author: stefan
 */

#ifndef FRAME_DATA_HPP
#define FRAME_DATA_HPP

#include "Light.hpp"
#include <VMMView/Model.hpp>
#include <VMMView/detail/Algorithm.hpp>
#include <VMMView/detail/MeshLoader.hpp>

class GlobalConfigWidget;

class FrameData {
public:
	FrameData();

	~FrameData() {
	}

	//todo: max number of lights can vary depending on opengl -> if possible replace by an opengl command which determines the correct value of a specific architecture
	static const size_t max_number_of_lights = 16;

	void apply_light() const;

	virtual bool load_model(const char* filename) {
		return MeshLoader::load(model_, filename);
	}

	const Model& model() const {
		return model_;
	}

	virtual std::vector<Light>& lights() {
		return lights_;
	}

	const std::vector<Light>& lights() const {
		return lights_;
	}

	const Algorithm::Ptr render_algorithm() const {
		return render_algorithm_;
	}

	Algorithm::Ptr render_algorithm() {
		return render_algorithm_;
	}

	virtual void render_algorithm(Algorithm::Ptr algo) {
		render_algorithm_ = algo;
	}

	Vector3 translation;
	float curquat[4];

protected:

	Algorithm::Ptr render_algorithm_;

	std::vector<Light> lights_;

	Model model_;

};

#endif /* FRAME_DATA_HPP */
