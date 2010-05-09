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

	virtual void load_model(std::string const& filename);

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

public:
	void export_scene(const char* filename);
	void import_scene(const char* filename);

public:
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

private:
	void init();

	template<typename T, typename Function>
	void for_each(T* stack, Function function) const
	{
		for (T* i = stack; i; i = i->next)
			function(i);
	}

protected:
	std::vector<Light> lights;

	std::string model_name;
	std::string ralgo_name;

private:
	Algorithm* algorithm_stack;
	MeshLoader* mesh_loader_stack;

	Algorithm* render_algorithm_;
	Model model_;
};

#endif /* FRAME_DATA_HPP */
