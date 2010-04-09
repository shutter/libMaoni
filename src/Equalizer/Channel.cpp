/*
 * Channel.cpp
 *
 *  Created on: 26.10.2009
 *      Author: vmml
 */

#include "Channel.hpp"
#include "FrameDataEq.hpp"
#include "Pipe.hpp"

void Channel::frameDraw(uint32_t spin)
{
	eq::Channel::frameDraw(spin);

	const FrameData& frame_data =
			static_cast<const Pipe*> (getPipe())->frame_data();

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(frame_data.translation.x(), frame_data.translation.y(),
			frame_data.translation.z());

	GLfloat rot_matrix[4][4];
	build_rotmatrix(rot_matrix, frame_data.curquat);
	glMultMatrixf(&rot_matrix[0][0]);

	frame_data.apply_light();
	if (frame_data.render_algorithm())
		frame_data.render_algorithm()->render(frame_data.model());
}
