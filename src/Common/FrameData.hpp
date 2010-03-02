/*
 * GlobalConfigParameter.hpp
 *
 *  Created on: 4 Aug 2009
 *      Author: stefan
 */

#ifndef FRAME_DATA_HPP
#define FRAME_DATA_HPP

#include "Light.hpp"
#include <Maoni/Model.hpp>
#include <Maoni/detail/Algorithm.hpp>
#include <Maoni/detail/MeshLoader.hpp>

class GlobalConfigWidget;

class FrameData {
public:
	FrameData(AlgorithmFactory* algorithm_factory_stack,
			MeshLoader* mesh_loader_stack);

	~FrameData() {
	}

	void apply_light() const;

	virtual bool load_model(const char* filename);

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

	bool add_light();
	unsigned int get_lights_size();
	Light& get_light(unsigned int i);

protected:

	Algorithm::Ptr render_algorithm_;

	Model model_;

private:
	//todo: max number of lights can vary depending on opengl -> if possible replace by an opengl command which determines the correct value of a specific architecture
	static const size_t max_number_of_lights = 8;
	std::vector<Light> lights_;

private:
	AlgorithmFactory* algorithm_factory_stack;
	MeshLoader* mesh_loader_stack;
};

#endif /* FRAME_DATA_HPP */
