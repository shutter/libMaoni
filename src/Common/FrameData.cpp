/*
 * GlobalConfigParameter.cpp
 *
 *  Created on: 21.08.2009
 *      Author: daniel
 */

#include "FrameData.hpp"
#include <GL/glew.h>
#include <boost/algorithm/string/predicate.hpp>

#include <teaset.h>

FrameData::FrameData(AlgorithmFactory* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack) :
	algorithm_factory_stack(algorithm_factory_stack), mesh_loader_stack(
			mesh_loader_stack) {
	// create LIGHT0 gl_diffuse(0.0,0.0,0.0,0.0) and gl_specular(1.0,1.0,1.0,1.0)
	lights().push_back(Light());
	lights()[0].setIs_light0(true);
	lights()[0].setName("LIGHT0 default");
	lights()[0].setDiffuse(Vector4(0.0, 0.0, 0.0, 0.0));
	lights()[0].setSpecular(Vector4(1.0, 1.0, 1.0, 1.0));

	GLint max_lights;
	glGetIntegerv(GL_MAX_LIGHTS, &max_lights);
	std::cout << "max lights: " << max_lights << std::endl;
}

void FrameData::draw() {
	apply_light();

	if (render_algorithm_)
		render_algorithm_->render(model_);
	else
		//		solid_teacup(1.f);
		solid_teapot(1.f);
	//		solid_teaspoon(1.f);
	//		model_.draw();
}

bool FrameData::load_model(const char* filename) {
	//	if (boost::algorithm::equals(filename, "<teacup>"))
	//		return load_bezier_surface(model_, teacup_nodes, teacup_rectangles);
	//
	//	if (boost::algorithm::equals(filename, "<teapot>"))
	//		return load_bezier_surface(model_, teapot_nodes, teapot_rectangles);
	//
	//	if (boost::algorithm::equals(filename, "<teaspoon>"))
	//		return load_bezier_surface(model_, teaspoon_nodes, teaspoon_rectangles);

	for (MeshLoader* i = mesh_loader_stack; i; i = i->next) {
		if (boost::algorithm::iends_with(filename, i->extension()))
			return i->load_i(model_, filename);
	}

	return false;
}

void FrameData::apply_light() const {
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable( GL_DEPTH_TEST);
	glEnable( GL_LIGHTING);

	for (std::size_t i = 0; i < max_number_of_lights; i++) {
		if ((lights().size() - 1) < i) {
			glDisable(GL_LIGHT0 + i);

		} else {

			if (!lights()[i].getIs_on()) {
				glDisable(GL_LIGHT0 + i);

			} else {

				glEnable(GL_LIGHT0 + i);
				glLightfv(GL_LIGHT0 + i, GL_AMBIENT,
						lights()[i].getAmbient().array);
				glLightfv(GL_LIGHT0 + i, GL_DIFFUSE,
						lights()[i].getDiffuse().array);
				glLightfv(GL_LIGHT0 + i, GL_SPECULAR,
						lights()[i].getSpecular().array);
				glLightfv(GL_LIGHT0 + i, GL_POSITION,
						lights()[i].getPosition().array);
				glLightf(GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION,
						lights()[i].getConst_att());
				glLightf(GL_LIGHT0 + i, GL_LINEAR_ATTENUATION,
						lights()[i].getLin_att());
				glLightf(GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION,
						lights()[i].getQuad_att());

				if (lights()[i].getIs_spot()) {
					glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF,
							lights()[i].getCut_off());
					glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION,
							lights()[i].getSpot_direction().array);
					glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT,
							lights()[i].getExponent());
				} else {
					glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 180.0);
					GLfloat spot_direction[] = { 0.0, 0.0, -1.0 };
					glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, spot_direction);
					glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, 0.0);
				}

				if (lights()[i].getShow_bulp()) {
					std::cout << lights()[i].getLight_box(2)[0] << " "
							<< lights()[i].getLight_box(2)[1] << " "
							<< lights()[i].getLight_box(2)[2] << std::endl;
					glPushMatrix();
					glColor3f(1.f, 1.f, 1.f);
					glBegin( GL_QUAD_STRIP);
					glVertex3fv(lights()[i].getLight_box(0).array);
					glVertex3fv(lights()[i].getLight_box(1).array);
					glVertex3fv(lights()[i].getLight_box(2).array);
					glVertex3fv(lights()[i].getLight_box(3).array);
					glVertex3fv(lights()[i].getLight_box(6).array);
					glVertex3fv(lights()[i].getLight_box(7).array);
					glVertex3fv(lights()[i].getLight_box(4).array);
					glVertex3fv(lights()[i].getLight_box(5).array);
					glVertex3fv(lights()[i].getLight_box(0).array);
					glVertex3fv(lights()[i].getLight_box(1).array);
					glEnd();

					glBegin( GL_QUADS);
					glVertex3fv(lights()[i].getLight_box(0).array);
					glVertex3fv(lights()[i].getLight_box(4).array);
					glVertex3fv(lights()[i].getLight_box(6).array);
					glVertex3fv(lights()[i].getLight_box(2).array);

					glVertex3fv(lights()[i].getLight_box(1).array);
					glVertex3fv(lights()[i].getLight_box(5).array);
					glVertex3fv(lights()[i].getLight_box(7).array);
					glVertex3fv(lights()[i].getLight_box(4).array);
					glEnd();

					if (lights()[i].getIs_spot()) {
						glBegin(GL_LINES);
						glVertex3fv(lights()[i].getPosition().array);
						glVertex3fv(lights()[i].getSpot_direction().array);
						glEnd();
					}

					glPopMatrix();
				}
			}
		}
	}
}

bool FrameData::add_light() {
	if (lights_.size() >= max_number_of_lights) {
		return false;
	} else {
		lights_.push_back(Light());
		return true;
	}
}

unsigned int FrameData::get_lights_size() {
	return lights_.size();
}

Light& FrameData::get_light(unsigned int i) {
	//std::cout << "light pointer: " << &(lights_.at(i)) << std::endl;
	return lights_.at(i);
}
