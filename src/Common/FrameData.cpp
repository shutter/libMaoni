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

bool FrameData::load_model(const char* filename)
{
	if (boost::algorithm::equals(filename, "<teacup>"))
		return model_.set_bezier_mesh(Model::teacup);

	if (boost::algorithm::equals(filename, "<teapot>"))
		return model_.set_bezier_mesh(Model::teapot);

	if (boost::algorithm::equals(filename, "<teaspoon>"))
		return model_.set_bezier_mesh(Model::teaspoon);

	if (boost::algorithm::equals(filename, "<spiral>"))
		return model_.set_bezier_mesh(Model::spiral);

	for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
	{
		if (boost::algorithm::iends_with(filename, i->extension()))
			return i->load(model_, filename) && model_.set_bezier_mesh(
					Model::none);
	}

	return false;
}

void FrameData::set_render_algorithm(std::string const& name)
{
	for (Algorithm* i = algorithm_stack; i; i = i->next)
	{
		if (name == i->name())
			render_algorithm_ = i;
	}
}

std::size_t FrameData::num_algorithms() const
{
	std::size_t num = 0;

	for (Algorithm* i = algorithm_stack; i; i = i->next)
		++num;

	return num;
}

std::size_t FrameData::num_loaders() const
{
	std::size_t num = 0;

	for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
		++num;

	return num;
}

const char* FrameData::mesh_loader_filters()
{
	if (mesh_loader_filters_.empty())
	{
		std::stringstream stream;
		stream << "All files (*.*)";
		for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
		{
			stream << ";;" << i->name() << " (*." << i->extension() << ")";
		}

		mesh_loader_filters_ = stream.str();
	}

	return mesh_loader_filters_.c_str();
}

void FrameData::draw() const
{
	if (render_algorithm_)
		render_algorithm_->render(model_);
	else
		model_.draw();
}
