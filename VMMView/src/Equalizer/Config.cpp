/*
 * Config.cpp
 *
 *  Created on: 26.10.2009
 *      Author: vmml
 */

#include "Config.hpp"
#include <eq/client/configEvent.h>
#include "../Common/trackball.h"

bool Config::handleEvent(const eq::ConfigEvent* event)
{
	// TODO: update model_view marix depending on events
	switch (event->data.type)
	{
	case eq::Event::POINTER_MOTION:
		if (dragging)
			mouse_update(event);
		last_x = event->data.pointerMotion.x;
		last_y = event->data.pointerMotion.y;
		break;

	case eq::Event::POINTER_BUTTON_PRESS:
		dragging = true;
		last_x = event->data.pointerMotion.x;
		last_y = event->data.pointerMotion.y;
		break;

	case eq::Event::POINTER_BUTTON_RELEASE:
		dragging = false;
		break;
	}

	return eq::Config::handleEvent(event);
}

void Config::mouse_update(const eq::ConfigEvent* event)
{
	float dx = float(event->data.pointerMotion.x - last_x) / 200.f;
	float dy = float(event->data.pointerMotion.y - last_y) / 200.f;

	if (event->data.pointerMotion.buttons == eq::PTR_BUTTON2
			|| (event->data.pointerMotion.buttons == eq::PTR_BUTTON1
					&& event->data.pointerMotion.buttons == eq::PTR_BUTTON3))
	{
		frame_data.translation.x() += dx;
		frame_data.translation.y() -= dy;
	}
	else if (event->data.pointerMotion.buttons == eq::PTR_BUTTON1)
	{
		trackball(lastquat, (2.0 * last_x - 800) / 800, //
				(600 - 2.0 * last_y) / 600, //
				(2.0 * event->data.pointerMotion.x - 800) / 800, //
				(600 - 2.0 * event->data.pointerMotion.y) / 600);
		add_quats(lastquat, frame_data.curquat, frame_data.curquat);
	}
	else if (event->data.pointerMotion.buttons == eq::PTR_BUTTON3)
	{
		frame_data.translation.z() += dy;
	}
	frame_data.mouse_event();
}
