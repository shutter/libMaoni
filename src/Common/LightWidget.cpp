/*
 * LightWidget.cpp
 *
 *  Created on: Dec 5, 2009
 *      Author: stefan
 */

#include "LightWidget.hpp"

LightWidget::LightWidget(int X, int Y, int W, int H, const char*L,
        FrameData& frame_data):Fl_Widget(X, Y, W, H, L), frame_data(frame_data), //
        light_box(X, Y, W, H), //
        light_counter(X+10, Y+10, 100, 25), //
        add_light(X+120, Y+10, 60, 25), del_light(X+180, Y+10, 60, 25), //
        pos_x(X+74, Y+40, 40, 25), pos_y(X+116, Y+40, 40, 25), //
        pos_z(X+158, Y+40, 40, 25), pos_v(X+200, Y+40, 40, 25), //
        ambient_r(X+74, Y+70, 40, 25), ambient_g(X+116, Y+70, 40, 25), //
        ambient_b(X+158, Y+70, 40, 25), ambient_a(X+200, Y+70, 40, 25), //
        diffuse_r(X+74, Y+100, 40, 25), diffuse_g(X+116, Y+100, 40, 25), //
        diffuse_b(X+158, Y+100, 40, 25), diffuse_a(X+200, Y+100, 40, 25), //
        specular_r(X+74, Y+130, 40, 25), specular_g(X+116, Y+130, 40, 25), //
        specular_b(X+158, Y+130, 40, 25), specular_a(X+200, Y+130, 40, 25), //
        const_att(X+200, Y+160, 40, 25), lin_att(X+200, Y+190, 40, 25), //
        quad_att(X+200, Y+220, 40, 25), //
        is_on(X+10, Y+250, 110, 25), show_bulp(X+130, Y+250, 110, 25), //
        is_spot(X+10, Y+280, 110, 25), //
        dir_x(X+116, Y+310, 40, 25), dir_y(X+158, Y+310, 40, 25), //
        dir_z(X+200, Y+310, 40, 25), //
        cut_off(X+74, Y+340, 40, 25), exponent(X+200, Y+340, 40, 25)
{
	frame_data.lights().push_back(Light());
	frame_data.lights()[0].diffuse = Vector4(1.f, 1.f, 1.f, 1.f);
	frame_data.lights()[0].specular = Vector4(1.f, 1.f, 1.f, 1.f);

	load_light(*this, 0);
}

LightWidget::~LightWidget()
{
	// TODO Auto-generated destructor stub
}

void LightWidget::draw()
{
	light_box.box(FL_ENGRAVED_BOX);
	light_box.color(FL_YELLOW);


	light_counter.callback(light_counter_cb, this);
	light_counter.step(1.0);
	light_counter.minimum(0);
	light_counter.maximum(frame_data.lights().size() - 1);
	light_counter.show();

	add_light.label("add");
	add_light.callback(add_light_cb, this);
	add_light.show();
	del_light.label("del");
	del_light.callback(del_light_cb, this);
	del_light.show();

	pos_x.label("position");
	pos_x.callback(pos_x_cb, this);
	pos_x.show();
	pos_y.callback(pos_y_cb, this);
	pos_y.show();
	pos_z.callback(pos_z_cb, this);
	pos_z.show();
	pos_v.callback(pos_v_cb, this);
	pos_v.show();

	ambient_r.label("ambient");
	ambient_r.callback(ambient_r_cb, this);
	ambient_r.show();
	ambient_g.callback(ambient_g_cb, this);
	ambient_g.show();
	ambient_b.callback(ambient_b_cb, this);
	ambient_b.show();
	ambient_a.callback(ambient_a_cb, this);
	ambient_a.show();

	diffuse_r.label("diffuse");
	diffuse_r.callback(diffuse_r_cb, this);
	diffuse_r.show();
	diffuse_g.callback(diffuse_g_cb, this);
	diffuse_g.show();
	diffuse_b.callback(diffuse_b_cb, this);
	diffuse_b.show();
	diffuse_a.callback(diffuse_a_cb, this);
	diffuse_a.show();

	specular_r.label("specular");
	specular_r.callback(specular_r_cb, this);
	specular_r.show();
	specular_g.callback(specular_g_cb, this);
	specular_g.show();
	specular_b.callback(specular_b_cb, this);
	specular_b.show();
	specular_a.callback(specular_a_cb, this);
	specular_a.show();

	const_att.label("constant attenuation");
	const_att.callback(const_att_cb, this);
	const_att.show();
	lin_att.label("linear attenuation");
	lin_att.callback(lin_att_cb, this);
	lin_att.show();
	quad_att.label("quadratic attenuation");
	quad_att.callback(quad_att_cb, this);
	quad_att.show();

	is_on.label("render light");
	is_on.callback(is_on_cb, this);
	is_on.show();
	show_bulp.label("show bulp");
	show_bulp.callback(show_bulp_cb, this);
	show_bulp.show();
	is_spot.label("is spotlight");
	is_spot.callback(is_spot_cb, this);
	is_spot.show();

	dir_x.label("spot direction");
	dir_x.callback(dir_x_cb, this);
	dir_x.show();
	dir_y.callback(dir_y_cb, this);
	dir_y.show();
	dir_z.callback(dir_z_cb, this);
	dir_z.show();

	cut_off.label("cut off");
	cut_off.callback(cut_off_cb, this);
	cut_off.show();

	exponent.label("exponent");
	exponent.callback(exponent_cb, this);
	exponent.show();

}


void LightWidget::light_counter_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	load_light(self, int(self.light_counter.value() + 0.5));
}

void LightWidget::add_light_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);

	if (self.frame_data.lights().size() >= self.frame_data.max_number_of_lights)
	{
		fl_message("Maximal number of light sources reached!");

	}
	else
	{
		self.frame_data.lights().push_back(Light());

		self.light_counter.value(self.light_counter.value() + 1.0);
		self.light_counter.maximum(self.frame_data.lights().size() - 1);
		load_light(self, int(self.light_counter.value() + 0.5));
	}
}
void LightWidget::del_light_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);

	if ((self.frame_data.lights().size() == 1) || (int(self.light_counter.value()
	        + 0.5) == 0))
	{
		fl_message("Can't delete light0!");
	}
	else
	{
		try
		{
			self.frame_data.lights().erase(self.frame_data.lights().begin()
			        + int(self.light_counter.value() + 0.5));
			self.light_counter.value(self.light_counter.value() - 1.0);
			self.light_counter.maximum(self.frame_data.lights().size() - 1);
			load_light(self, int(self.light_counter.value() + 0.5));
		}
		catch (std::exception& e)
		{
			std::cerr << "Unable to remove light:  " << e.what() << std::endl;
		}
	}
}

void LightWidget::pos_x_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).position[0]
	        = boost::lexical_cast<float>(self.pos_x.value());
}
void LightWidget::pos_y_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).position[1]
	        = boost::lexical_cast<float>(self.pos_y.value());
}
void LightWidget::pos_z_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).position[2]
	        = boost::lexical_cast<float>(self.pos_z.value());
}
void LightWidget::pos_v_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).position[3]
	        = boost::lexical_cast<float>(self.pos_v.value());
}

void LightWidget::ambient_r_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).ambient[0]
	        = boost::lexical_cast<float>(self.ambient_r.value());
}
void LightWidget::ambient_g_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).ambient[1]
	        = boost::lexical_cast<float>(self.ambient_g.value());
}
void LightWidget::ambient_b_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).ambient[2]
	        = boost::lexical_cast<float>(self.ambient_b.value());
}
void LightWidget::ambient_a_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).ambient[3]
	        = boost::lexical_cast<float>(self.ambient_a.value());
}

void LightWidget::diffuse_r_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).diffuse[0]
	        = boost::lexical_cast<float>(self.diffuse_r.value());
}
void LightWidget::diffuse_g_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).diffuse[1]
	        = boost::lexical_cast<float>(self.diffuse_g.value());
}
void LightWidget::diffuse_b_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).diffuse[2]
	        = boost::lexical_cast<float>(self.diffuse_b.value());
}
void LightWidget::diffuse_a_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).diffuse[3]
	        = boost::lexical_cast<float>(self.diffuse_a.value());
}

void LightWidget::specular_r_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).specular[0]
	        = boost::lexical_cast<float>(self.specular_r.value());
}
void LightWidget::specular_g_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).specular[1]
	        = boost::lexical_cast<float>(self.specular_g.value());
}
void LightWidget::specular_b_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).specular[2]
	        = boost::lexical_cast<float>(self.specular_b.value());
}
void LightWidget::specular_a_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).specular[3]
	        = boost::lexical_cast<float>(self.specular_a.value());
}

void LightWidget::const_att_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).const_att
	        = boost::lexical_cast<float>(self.const_att.value());
}

void LightWidget::lin_att_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).lin_att
	        = boost::lexical_cast<float>(self.lin_att.value());
}

void LightWidget::quad_att_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).quad_att
	        = boost::lexical_cast<float>(self.quad_att.value());
}

void LightWidget::is_on_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);

	if (self.is_on.value())
	{
		self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).is_on
		        = true;
	}
	else
	{
		self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).is_on
		        = false;
	}
}

void LightWidget::show_bulp_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);

	if (self.show_bulp.value())
	{
		self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).show_bulp
		        = true;
	}
	else
	{
		self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).show_bulp
		        = false;
	}
}

void LightWidget::is_spot_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);

	if (self.is_spot.value())
	{
		self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).is_spot
		        = true;
		self.dir_x.activate();
		self.dir_y.activate();
		self.dir_z.activate();
		self.cut_off.activate();
		self.exponent.activate();
	}
	else
	{
		self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).is_spot
		        = false;
		self.dir_x.deactivate();
		self.dir_y.deactivate();
		self.dir_z.deactivate();
		self.cut_off.deactivate();
		self.exponent.deactivate();
	}
}

void LightWidget::dir_x_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).spot_direction[0]
	        = boost::lexical_cast<float>(self.dir_x.value());
}
void LightWidget::dir_y_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).spot_direction[1]
	        = boost::lexical_cast<float>(self.dir_y.value());
}
void LightWidget::dir_z_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).spot_direction[2]
	        = boost::lexical_cast<float>(self.dir_z.value());
}

void LightWidget::cut_off_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).cut_off
	        = boost::lexical_cast<float>(self.cut_off.value());
}

void LightWidget::exponent_cb(Fl_Widget*, void* widget)
{
	LightWidget& self = *reinterpret_cast<LightWidget*> (widget);
	self.frame_data.lights().at(int(self.light_counter.value() + 0.5)).exponent
	        = boost::lexical_cast<float>(self.exponent.value());
}

void LightWidget::load_light(LightWidget& self, int i)
{
	self.pos_x.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).position[0]).c_str());
	self.pos_y.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).position[1]).c_str());
	self.pos_z.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).position[2]).c_str());
	self.pos_v.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).position[3]).c_str());

	self.ambient_r.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).ambient[0]).c_str());
	self.ambient_g.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).ambient[1]).c_str());
	self.ambient_b.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).ambient[2]).c_str());
	self.ambient_a.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).ambient[3]).c_str());

	self.diffuse_r.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).diffuse[0]).c_str());
	self.diffuse_g.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).diffuse[1]).c_str());
	self.diffuse_b.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).diffuse[2]).c_str());
	self.diffuse_a.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).diffuse[3]).c_str());

	self.specular_r.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).specular[0]).c_str());
	self.specular_g.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).specular[1]).c_str());
	self.specular_b.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).specular[2]).c_str());
	self.specular_a.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).specular[3]).c_str());

	self.const_att.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).const_att).c_str());
	self.lin_att.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).lin_att).c_str());
	self.quad_att.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).quad_att).c_str());

	self.dir_x.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).spot_direction[0]).c_str());
	self.dir_y.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).spot_direction[1]).c_str());
	self.dir_z.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).spot_direction[2]).c_str());

	self.cut_off.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).cut_off).c_str());
	self.exponent.value(boost::lexical_cast<std::string>(
	        self.frame_data.lights().at(i).exponent).c_str());

	if (self.frame_data.lights().at(i).is_on)
	{
		self.is_on.value(true);
	}
	else
	{
		self.is_on.value(false);
	}

	if (int(self.light_counter.value() + 0.5) == 0)
	{
		self.is_spot.deactivate();
	}
	else
	{
		self.is_spot.activate();
	}

	if (self.frame_data.lights().at(i).is_spot)
	{
		self.is_spot.value(true);
		self.dir_x.activate();
		self.dir_y.activate();
		self.dir_z.activate();
		self.cut_off.activate();
		self.exponent.activate();
	}
	else
	{
		self.is_spot.value(0);
		self.dir_x.deactivate();
		self.dir_y.deactivate();
		self.dir_z.deactivate();
		self.cut_off.deactivate();
		self.exponent.deactivate();
	}
}
