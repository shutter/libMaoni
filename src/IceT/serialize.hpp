/*
 * serialize.hpp
 *
 *  Created on: 07.04.2010
 *      Author: daniel
 */

#ifndef MAONI_ICET_SERIALIZE_HPP
#define MAONI_ICET_SERIALIZE_HPP

#include "../Common/Light.hpp"
#include "Tile.hpp"

namespace boost
{
namespace serialization
{

template<class Archive>
void serialize(Archive& archive, Light& light, const unsigned int /*version*/)
{
	archive & light.enabled;
	archive & light.show_bulp;
	archive & light.position;

	archive & light.ambient;
	archive & light.diffuse;
	archive & light.specular;

	archive & light.const_att;
	archive & light.lin_att;
	archive & light.quad_att;

	archive & light.is_spot;
	archive & light.spot_direction;
	archive & light.cut_off;
	archive & light.exponent;
}

} // namespace serialization
} // namespace boost


#endif /* MAONI_ICET_SERIALIZE_HPP */
