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
#include <string>

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

	Color const& getAmbient() const
	{
		return ambient;
	}

	float getConst_att() const
	{
		return const_att;
	}

	float getCut_off() const
	{
		return cut_off;
	}

	Color const& getDiffuse() const
	{
		return diffuse;
	}

	float getExponent() const
	{
		return exponent;
	}

	bool getIs_on() const
	{
		return enabled;
	}

	bool getIs_spot() const
	{
		return is_spot;
	}

	float getLin_att() const
	{
		return lin_att;
	}

	Vector3 getPosition() const
	{
		return position;
	}

	float getQuad_att() const
	{
		return quad_att;
	}

	bool getShow_bulp() const
	{
		return show_bulp;
	}

	Color const& getSpecular() const
	{
		return specular;
	}

	Vector3 getSpot_direction() const
	{
		return spot_direction;
	}

	void setAmbient(Color const& ambient)
	{
		this->ambient = ambient;
	}

	void setConst_att(float const_att)
	{
		this->const_att = const_att;
	}

	void setCut_off(float cut_off)
	{
		this->cut_off = cut_off;
	}

	void setDiffuse(Color const& diffuse)
	{
		this->diffuse = diffuse;
	}

	void setExponent(float exponent)
	{
		this->exponent = exponent;
	}

	void setIs_on(bool is_on)
	{
		this->enabled = is_on;
	}

	void setIs_spot(bool is_spot)
	{
		this->is_spot = is_spot;
	}

	void setLin_att(float lin_att)
	{
		this->lin_att = lin_att;
	}

	void setPosition(Vector3 position)
	{
		this->position = position;
	}

	void setQuad_att(float quad_att)
	{
		this->quad_att = quad_att;
	}

	void setShow_bulp(bool show_bulp)
	{
		this->show_bulp = show_bulp;
	}

	void setSpecular(Color const& specular)
	{
		this->specular = specular;
	}

	void setSpot_direction(Vector3 spot_direction)
	{
		this->spot_direction = spot_direction;
	}
};

#endif /* LIGHT_HPP */
