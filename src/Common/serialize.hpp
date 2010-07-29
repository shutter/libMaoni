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

#ifndef MAONI_SERIALIZE_HPP
#define MAONI_SERIALIZE_HPP

#include <Maoni/Enum.hpp>
#include <Maoni/Color.hpp>
#include <Maoni/Vector.hpp>
#include <Maoni/Texture.hpp>
#include <Maoni/RenderAlgorithm.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/la/all.hpp>

namespace boost
{
namespace serialization
{
using namespace boost::la;

template<class Archive>
void serialize(Archive& archive, Color& color, unsigned int)
{
	float red = color[0], green = color[1], blue = color[2], alpha = color[3];
	archive & make_nvp("red", red) & make_nvp("green", green);
	archive & make_nvp("blue", blue) & make_nvp("alpha", alpha);
	color = Color(red, green, blue, alpha);
}

template<class Archive>
void serialize(Archive& archive, Vec2& vector2, unsigned int)
{
	archive & make_nvp("x", vector2 | X) & make_nvp("y", vector2 | Y);
}

template<class Archive>
void serialize(Archive& archive, Vec3& vector3, unsigned int)
{
	archive & make_nvp("x", vector3 | X) & make_nvp("y", vector3 | Y)
			& make_nvp("z", vector3 | Z);
}

template<class Archive>
void serialize(Archive& archive, Vec4& vector4, unsigned int)
{
	archive & make_nvp("x", vector4 | X) & make_nvp("y", vector4 | Y)
			& make_nvp("z", vector4 | Z) & make_nvp("w", vector4 | W);
}

template<class Archive>
class AlgorithmSerializer: public AlgorithmConfig
{
public:
	AlgorithmSerializer(Archive& archive) :
		archive(archive)
	{
	}

private:
	void property(const char* name, int& value)
	{
		archive & make_nvp(name, value);
	}

	void property(const char* name, bool& value)
	{
		archive & make_nvp(name, value);
	}

	void property(const char* name, float& value)
	{
		archive & make_nvp(name, value);
	}

	void property(const char* name, double& value)
	{
		archive & make_nvp(name, value);
	}

	void property(const char* name, Enum& value)
	{
		int tmp = value;
		archive & make_nvp(name, tmp);
		value = tmp;
	}

	void property(const char* name, Path& value)
	{
		std::string tmp(value.path().c_str(), value.path().size());
		archive & make_nvp(name, tmp);
		value.path(tmp);
	}

	void property(const char* name, Color& value)
	{
		archive & make_nvp(name, value);
	}

	void property(const char* name, ShaderProgram& value)
	{
	}

private:
	Archive& archive;
};

template<class Archive>
void serialize(Archive& archive, RenderAlgorithm& algorithm, unsigned int)
{
	AlgorithmSerializer<Archive> serializer(archive);
	algorithm.config(serializer);
}

} // namespace serialization
} // namespace boost

#endif /* MAONI_SERIALIZE_HPP */
