/*
 * serialize.hpp
 *
 *  Created on: 07.05.2010
 *      Author: daniel
 */

#ifndef MAONI_SERIALIZE_HPP
#define MAONI_SERIALIZE_HPP

#include <Maoni/Color.hpp>
#include <Maoni/Vector.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/la/all.hpp>

namespace boost
{
namespace serialization
{
using namespace boost::la;

template<class Archive>
void save(Archive& archive, const Color& color, unsigned int)
{
	archive & make_nvp("red", color[0]) & make_nvp("green", color[1])
			& make_nvp("blue", color[2]) & make_nvp("alpha", color[3]);
}

template<class Archive>
void load(Archive& archive, Color& color, unsigned int)
{
	float red, green, blue, alpha;
	archive & make_nvp("red", red) & make_nvp("green", green);
	archive & make_nvp("blue", blue) & make_nvp("alpha", alpha);
	color = Color(red, green, blue, alpha);
}

template<class Archive>
void serialize(Archive& archive, Vector2& vector2, unsigned int)
{
	archive & make_nvp("x", vector2 | X) & make_nvp("y", vector2 | Y);
}

template<class Archive>
void serialize(Archive& archive, Vector3& vector3, unsigned int)
{
	archive & make_nvp("x", vector3 | X) & make_nvp("y", vector3 | Y)
			& make_nvp("z", vector3 | Z);
}

template<class Archive>
void serialize(Archive& archive, Vector4& vector4, unsigned int)
{
	archive & make_nvp("x", vector4 | X) & make_nvp("y", vector4 | Y)
			& make_nvp("z", vector4 | Z) & make_nvp("w", vector4 | W);
}

} // namespace serialization
} // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(Color)

#endif /* MAONI_SERIALIZE_HPP */
