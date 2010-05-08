#include "FrameData.hpp"
#include <boost/algorithm/string/predicate.hpp>
#include <sstream>

FrameData::FrameData(Algorithm* algorithm_stack, MeshLoader* mesh_loader_stack) :
	algorithm_stack(algorithm_stack), mesh_loader_stack(mesh_loader_stack),
			render_algorithm_(0)
{
	init();
}

FrameData::FrameData(FrameData const& other) :
	algorithm_stack(other.algorithm_stack), //
			mesh_loader_stack(other.mesh_loader_stack), render_algorithm_(0)
{
	init();
}

void FrameData::init()
{
	lights.resize(16); // todo; query this constant
	std::memset(&lights[0], 0, lights.size() * sizeof(Light));

	//! light 0 defaults
	lights[0].enabled = true;
	lights[0].position = Vector3(1.0, 0.0, 1.0);
	lights[0].diffuse = Color(1.0, 0.0, 0.0, 1.0);
	lights[0].specular = Color(1.0, 1.0, 0.0, 1.0);
}

void FrameData::load_model(const char* filename)
{
	for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
	{
		if (boost::algorithm::iends_with(filename, i->extension()))
			i->load(model_, filename);
	}
}

class algo_setter
{
public:
	algo_setter(std::string const& name, Algorithm*& algorithm) :
		name(name), algorithm(algorithm)
	{
	}

	void operator()(Algorithm*& algo)
	{
		if (name == algo->name())
			algorithm = algo;
	}

private:
	std::string const& name;
	Algorithm*& algorithm;
};

void FrameData::set_render_algorithm(std::string const& name)
{
	for_each_algorithm(algo_setter(name, render_algorithm_));
}

class count
{
public:
	count(std::size_t& value) :
		value(value)
	{
	}

	template<typename T>
	void operator()(T)
	{
		++value;
	}

private:
	std::size_t& value;
};

std::size_t FrameData::num_algorithms() const
{
	std::size_t num = 0;
	for_each_algorithm(count(num));
	return num;
}

std::size_t FrameData::num_loaders() const
{
	std::size_t num = 0;
	for_each_loader(count(num));
	return num;
}

void FrameData::draw() const
{
	if (render_algorithm_)
		render_algorithm_->render(model_);
	else
		model_.draw();
}
