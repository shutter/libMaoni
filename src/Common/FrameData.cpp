/*
 * GlobalConfigParameter.cpp
 *
 *  Created on: 21.08.2009
 *      Author: daniel
 */

#include "FrameData.hpp"
#include <GL/glew.h>
#include "trackball.h"

FrameData::FrameData() :
	translation(0, 0, -2) {
	trackball(curquat, 0.0, 0.0, 0.0, 0.0);

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

				// TODO: alternative to glutSolidSphere()
				/*	if (light.getShow_bulp())
				 {
				 glPushMatrix();
				 glTranslatef(light.getPosition()[0], light.getPosition()[1], light.getPosition()[2]);
				 glColor3f(1.f, 1.f, 1.f);
				 glutSolidSphere(0.01, 4, 4);
				 glPopMatrix();
				 }*/
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
