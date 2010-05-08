#ifndef FRAME_DATA_HPP
#define FRAME_DATA_HPP

#include "Light.hpp"
#include <Maoni/Model.hpp>
#include <Maoni/detail/Algorithm.hpp>
#include <Maoni/detail/MeshLoader.hpp>
#include <string>

class FrameData
{
public:
	FrameData(Algorithm* algorithm_factory_stack,
			MeshLoader* mesh_loader_stack);

	FrameData(FrameData const& other);

	template<typename Function>
	void for_each_algorithm(Function function) const
	{
		for_each(algorithm_stack, function);
	}

	template<typename Function>
	void for_each_loader(Function function) const
	{
		for_each(mesh_loader_stack, function);
	}

	virtual void load_model(const char* filename);

	virtual void set_render_algorithm(std::string const& name);

	void config_algorithm(AlgorithmConfig& manager)
	{
		if (render_algorithm_)
			render_algorithm_->config(manager);
	}

	//! get the amount of render algorithms
	std::size_t num_algorithms() const;

	//! get the amount of mesh loaders
	std::size_t num_loaders() const;

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

	template<typename T, typename Function>
	void for_each(T* stack, Function function) const
	{
		for (T* i = stack; i; i = i->next)
			function(i);
	}

public:
	// FIXME: for testing made public, should be protected:
	std::vector<Light> lights;

	//private:
	Algorithm* algorithm_stack;
	MeshLoader* mesh_loader_stack;

	std::string mesh_loader_filters_;

	Algorithm* render_algorithm_;

	Model model_;
};

#endif /* FRAME_DATA_HPP */
