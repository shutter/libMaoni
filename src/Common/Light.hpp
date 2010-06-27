/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	Vec3 position;

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
	Vec3 spot_direction;
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
