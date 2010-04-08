/*
 * Light.hpp
 *
 *  Created on: 7 Aug 2009
 *      Author: stefan
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Maoni/Color.hpp>
#include <Maoni/Vector.hpp>

struct Light
{
	bool enabled;
	bool show_bulp;
	Vector3 position;

	//! Color
	Color ambient;
	Color diffuse;
	Color specular;

	//! Attenuation
	float const_att;
	float lin_att;
	float quad_att;

	//! Spot
	bool is_spot;
	Vector3 spot_direction;
	float cut_off;
	float exponent;
};

#endif /* LIGHT_HPP */
