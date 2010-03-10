/*
 * GlobalConfigParameter.cpp
 *
 *  Created on: 21.08.2009
 *      Author: daniel
 */

#include "FrameData.hpp"
#include <GL/glew.h>
#include <boost/algorithm/string/predicate.hpp>

#include <Maoni/Teaset.h>

FrameData::FrameData(AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack) :
	algorithm_factory_stack(algorithm_factory_stack), mesh_loader_stack(
			mesh_loader_stack)
{
	// create LIGHT0 gl_diffuse(0.0,0.0,0.0,0.0) and gl_specular(1.0,1.0,1.0,1.0)
	lights().push_back(Light());
	lights()[0].setIs_light0(true);
	lights()[0].setName("LIGHT0 default");
	lights()[0].setDiffuse(Color(0.0, 0.0, 0.0, 0.0));
	lights()[0].setSpecular(Color(1.0, 1.0, 1.0, 1.0));

	GLint max_lights;
	glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	std::cout << "max lights: " << max_lights << std::endl;
}

void FrameData::draw()
{
	apply_light();

	if (render_algorithm_)
		render_algorithm_->render(model_);
	else
		solid_teapot(1.f);
}

bool FrameData::load_model(const char* filename)
{
	if (boost::algorithm::equals(filename, "<teacup>"))
		return model_.set_bezier_mesh(Model::teacup);

	if (boost::algorithm::equals(filename, "<teapot>"))
		return model_.set_bezier_mesh(Model::teapot);

	if (boost::algorithm::equals(filename, "<teaspoon>"))
		return model_.set_bezier_mesh(Model::teaspoon);

	for (MeshLoader* i = mesh_loader_stack; i; i = i->next)
	{
		if (boost::algorithm::iends_with(filename, i->extension()))
			return i->load_i(model_, filename) && model_.set_bezier_mesh(Model::none);
	}

	return false;
}

void FrameData::apply_light() const
{
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	for (std::size_t i = 0; i < max_number_of_lights; i++)
	{
		if ((lights().size() - 1) < i)
			glDisable(GL_LIGHT0 + i);
		else
			lights()[i].apply(i);
	}

}

bool FrameData::add_light()
{
	if (lights_.size() >= max_number_of_lights)
	{
		return false;
	}
	else
	{
		lights_.push_back(Light());
		return true;
	}
}

unsigned int FrameData::get_lights_size()
{
	return lights_.size();
}

Light& FrameData::get_light(unsigned int i)
{
	//std::cout << "light pointer: " << &(lights_.at(i)) << std::endl;
	return lights_.at(i);
}
