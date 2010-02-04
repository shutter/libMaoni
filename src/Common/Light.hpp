/*
 * Light.hpp
 *
 *  Created on: 7 Aug 2009
 *      Author: stefan
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Maoni/Vector.hpp>

class Light
{
public:
	Light() :
		name("Light"), position(0.f, 0.f, 1.f, 0.f), ambient(0.f, 0.f, 0.f, 1.f), //
				diffuse(0.f, 0.f, 0.f, 1.f), specular(0.f, 0.f, 0.f, 1.f), //
				const_att(1.f), lin_att(0.f), quad_att(0.f), //
				is_spot(false), spot_direction(0.f, 0.f, -1.f), cut_off(180.f), //
				exponent(0.f), is_on(true), show_bulp(false), is_light0(false)
	{
	}

	std::string name;
	Vector4 position;
	Vector4 ambient;
	Vector4 diffuse;
	Vector4 specular;
	float const_att;
	float lin_att;
	float quad_att;
	bool is_spot;
	Vector3 spot_direction;
	float cut_off;
	float exponent;
	bool is_on;
	bool show_bulp;

	// light0 may not be spot and needs gl_diffuse(0.0,0.0,0.0,0.0) and gl_specular(1.0,1.0,1.0,1.0)
	bool is_light0;

private:

};

#endif /* LIGHT_HPP */
