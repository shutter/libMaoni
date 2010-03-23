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
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>
#include <QFile>

class GlobalConfigWidget;

class FrameData
{
public:
	FrameData(AlgorithmFactory* algorithm_factory_stack,
			MeshLoader* mesh_loader_stack);

	~FrameData()
	{
	}

	void draw() const;

	bool load_model(const char* filename);

	void set_render_algorithm(std::string const& name);

	//! get the amount of render algorithms
	std::size_t num_algorithms() const;

	//! get the amount of mesh loaders
	std::size_t num_loaders() const;

	bool add_light();
	bool remove_light(int i);
	unsigned int get_lights_size();
	Light& get_light(unsigned int i);
	int export_lights(std::string const& filename);
	int import_lights(std::string const& filename);


private:
	//todo: max number of lights can vary depending on opengl -> if possible replace by an opengl command which determines the correct value of a specific architecture
	static const size_t max_number_of_lights = 8;
	std::vector<Light> lights_;
	QDomElement LightToNode( QDomDocument &d, const Light &l );
	void make_light0(Light& l);


private:
	AlgorithmFactory* algorithm_factory_stack;
	MeshLoader* mesh_loader_stack;

	Algorithm::Ptr render_algorithm_;
	Model model_;
};

#endif /* FRAME_DATA_HPP */
