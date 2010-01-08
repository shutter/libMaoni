/*
 * LightWidget.h
 *
 *  Created on: Dec 5, 2009
 *      Author: stefan
 */

#ifndef LIGHTWIDGET_H_
#define LIGHTWIDGET_H_

#include "FrameData.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Simple_Counter.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <FL/fl_ask.H>

class LightWidget: public Fl_Widget
{
public:
	LightWidget(int X, int Y, int W, int H, const char*L,
	        FrameData& frame_data);
	virtual ~LightWidget();
	void draw();

private:
	static void load_light(LightWidget& self, int i);

	FrameData& frame_data;

	Fl_Box light_box;

	Fl_Simple_Counter light_counter;
	static void light_counter_cb(Fl_Widget*, void*);
	Fl_Button add_light;
	static void add_light_cb(Fl_Widget*, void* window);
	Fl_Button del_light;
	static void del_light_cb(Fl_Widget*, void* window);

	Fl_Float_Input pos_x, pos_y, pos_z, pos_v;
	static void pos_x_cb(Fl_Widget*, void* window);
	static void pos_y_cb(Fl_Widget*, void* window);
	static void pos_z_cb(Fl_Widget*, void* window);
	static void pos_v_cb(Fl_Widget*, void* window);

	Fl_Float_Input ambient_r, ambient_g, ambient_b, ambient_a;
	static void ambient_r_cb(Fl_Widget*, void* window);
	static void ambient_g_cb(Fl_Widget*, void* window);
	static void ambient_b_cb(Fl_Widget*, void* window);
	static void ambient_a_cb(Fl_Widget*, void* window);

	Fl_Float_Input diffuse_r, diffuse_g, diffuse_b, diffuse_a;
	static void diffuse_r_cb(Fl_Widget*, void* window);
	static void diffuse_g_cb(Fl_Widget*, void* window);
	static void diffuse_b_cb(Fl_Widget*, void* window);
	static void diffuse_a_cb(Fl_Widget*, void* window);

	Fl_Float_Input specular_r, specular_g, specular_b, specular_a;
	static void specular_r_cb(Fl_Widget*, void* window);
	static void specular_g_cb(Fl_Widget*, void* window);
	static void specular_b_cb(Fl_Widget*, void* window);
	static void specular_a_cb(Fl_Widget*, void* window);

	Fl_Float_Input const_att, lin_att, quad_att;
	static void const_att_cb(Fl_Widget*, void* window);
	static void lin_att_cb(Fl_Widget*, void* window);
	static void quad_att_cb(Fl_Widget*, void* window);

	Fl_Check_Button is_on;
	static void is_on_cb(Fl_Widget*, void* window);
	Fl_Check_Button show_bulp;
	static void show_bulp_cb(Fl_Widget*, void* window);
	Fl_Check_Button is_spot;
	static void is_spot_cb(Fl_Widget*, void* window);

	Fl_Float_Input dir_x, dir_y, dir_z;
	static void dir_x_cb(Fl_Widget*, void* window);
	static void dir_y_cb(Fl_Widget*, void* window);
	static void dir_z_cb(Fl_Widget*, void* window);

	Fl_Float_Input cut_off, exponent;
	static void cut_off_cb(Fl_Widget*, void* window);
	static void exponent_cb(Fl_Widget*, void* window);
};

#endif /* LIGHTWIDGET_H_ */
