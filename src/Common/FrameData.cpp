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

#include "FrameData.hpp"
#include <boost/algorithm/string/predicate.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "serialize.hpp"
#include <fstream>

FrameData::FrameData(RenderAlgorithm* algorithm_stack, MeshLoader* mesh_loader_stack) :
	renderer(0), algorithm_stack(algorithm_stack), mesh_loader_stack(
		mesh_loader_stack)
{
	init();
}

FrameData::FrameData(FrameData const& other) :
	renderer(0), algorithm_stack(other.algorithm_stack), //
		mesh_loader_stack(other.mesh_loader_stack)
{
	init();
}

void FrameData::init()
{
	lights.resize(16); // todo; query this constant
	std::memset(&lights[0], 0, lights.size() * sizeof(Light));

	//! light 0 defaults
	lights[0].enabled = true;
	lights[0].position = Vec3(1.0, 0.0, 1.0);
	lights[0].diffuse = Color(1.0, 0.0, 0.0, 1.0);
	lights[0].specular = Color(1.0, 1.0, 0.0, 1.0);

	model_.reset(new Model);
}

void FrameData::load_model(std::string const& filename)
{
	for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
	{
		if (boost::algorithm::iends_with(filename, i->extension()))
			i->load(model_, filename.c_str());
	}

	//! make sure we have a valid model even if the loader failed
	if (!model_)
		model_.reset(new Model);

	model_name = filename;
}

class algo_setter
{
public:
	algo_setter(std::string const& name, RenderAlgorithm*& algorithm) :
		name(name), algorithm(algorithm)
	{
	}

	void operator()(RenderAlgorithm*& algo)
	{
		if (name == algo->name())
			algorithm = algo;
	}

private:
	std::string const& name;
	RenderAlgorithm*& algorithm;
};

void FrameData::set_render_algorithm(std::string const& name)
{
	for_each_algorithm(algo_setter(name, renderer));
	ralgo_name = name;
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
	assert(model_);

	if (renderer)
		renderer->render(*model_);
	else
		model_->draw();

	logo.draw();
}

void FrameData::export_scene(const char* filename)
{
	std::ofstream file(filename);
	if (!file)
		return;

	boost::archive::xml_oarchive archive(file);
	archive << boost::serialization::make_nvp("lights", lights);
	archive << boost::serialization::make_nvp("model", model_name);
	archive << boost::serialization::make_nvp("ralgo_name", ralgo_name);
	archive << boost::serialization::make_nvp("renderer", *renderer);
}

void FrameData::import_scene(const char* filename)
{
	std::ifstream file(filename);
	if (!file)
		return;

	boost::archive::xml_iarchive archive(file);
	archive >> boost::serialization::make_nvp("lights", lights);

	archive >> boost::serialization::make_nvp("model", model_name);
	load_model(model_name);

	archive >> boost::serialization::make_nvp("renderer", ralgo_name);
	set_render_algorithm(ralgo_name);

	archive >> boost::serialization::make_nvp("algorithm", *renderer);
}
