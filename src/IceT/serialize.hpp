/*
 * serialize.hpp
 *
 *  Created on: 07.04.2010
 *      Author: daniel
 */

#ifndef MAONI_ICET_SERIALIZE_HPP
#define MAONI_ICET_SERIALIZE_HPP

#include "../Common/Light.hpp"
#include "../Common/Tile.hpp"

namespace boost
{
namespace serialization
{

template<class Archive>
void serialize(Archive& archive, Light& light, const unsigned int /*version*/)
{
	//	archive & light.name;
	//	archive & light.position;
	//	archive & light.ambient;
}

} // namespace serialization
} // namespace boost


#endif /* MAONI_ICET_SERIALIZE_HPP */
