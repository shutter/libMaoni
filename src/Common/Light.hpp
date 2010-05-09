/*
 * Light.hpp
 *
 *  Created on: 7 Aug 2009
 *      Author: stefan
 */

#ifndef MAONI_LIGHT_HPP
#define MAONI_LIGHT_HPP

#include <Maoni/Color.hpp>
#include <Maoni/Vector.hpp>
#include <boost/serialization/nvp.hpp>

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

	template<class Archive>
	void serialize(Archive & archive, unsigned int)
	{
		archive & BOOST_SERIALIZATION_NVP(enabled);
		if (!enabled)
			return;

		archive & BOOST_SERIALIZATION_NVP(show_bulp);
		archive & BOOST_SERIALIZATION_NVP(position);

		archive & BOOST_SERIALIZATION_NVP(ambient);
		archive & BOOST_SERIALIZATION_NVP(diffuse);
		archive & BOOST_SERIALIZATION_NVP(specular);

		archive & BOOST_SERIALIZATION_NVP(const_att);
		archive & BOOST_SERIALIZATION_NVP(lin_att);
		archive & BOOST_SERIALIZATION_NVP(quad_att);

		archive & BOOST_SERIALIZATION_NVP(is_spot);
		if (!is_spot)
			return;

		archive & BOOST_SERIALIZATION_NVP(spot_direction);
		archive & BOOST_SERIALIZATION_NVP(cut_off);
		archive & BOOST_SERIALIZATION_NVP(exponent);
	}
};

#endif /* MAONI_LIGHT_HPP */
