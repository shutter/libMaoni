/*
 * ConfigWindow.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#ifndef CONFIG_WINDOW_HPP
#define CONFIG_WINDOW_HPP

#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include <VMMView/detail/Algorithm.hpp>
#include "LightWidget_old.hpp"


class ConfigWindow: public Fl_Window
{
public:
	ConfigWindow(FrameData& frame_data) :
		Fl_Window(252, 386, "Lights"), //
				light_widget(3, 3, 246, 380, 0, frame_data)
	{
		end();
		show();
	}

private:
	LightWidget_old light_widget;
};

#endif /* CONFIG_WINDOW_HPP */
