#ifndef FRAME_DATA_HPP
#define FRAME_DATA_HPP

#include "Light.hpp"
#include <Maoni/Model.hpp>
#include <Maoni/detail/Algorithm.hpp>
#include <Maoni/detail/MeshLoader.hpp>

class FrameData
{
public:
	FrameData(AlgorithmFactory* algorithm_factory_stack,
			MeshLoader* mesh_loader_stack);

	FrameData(FrameData const& other);

	virtual bool load_model(const char* filename);

	virtual void set_render_algorithm(std::string const& name);

	//! get the amount of render algorithms
	std::size_t num_algorithms() const;

	//! get the amount of mesh loaders
	std::size_t num_loaders() const;

	const char* mesh_loader_filters();

	std::size_t num_lights() const
	{
		return lights.size();
	}

	virtual Light& light(std::size_t i)
	{
		return lights[i];
	}

	const Light& light(std::size_t i) const
	{
		return lights[i];
	}

	void draw() const;

private:
	void init();

protected:
	std::vector<Light> lights;

private:
	AlgorithmFactory* algorithm_factory_stack;
	MeshLoader* mesh_loader_stack;

	std::string mesh_loader_filters_;

	Algorithm::Ptr render_algorithm_;

	Model model_;
};

#endif /* FRAME_DATA_HPP */
