/*
 * ImportExport.cpp
 *
 *  Created on: 08.04.2010
 *      Author: daniel
 */

#include "ImportExport.hpp"
#include "FrameData.hpp"

#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "serialize.hpp"

int export_lights(std::string const& filename, FrameData const& framedata)
{
	std::ofstream file(filename.c_str());
	if (!file)
		return -1;

	boost::archive::xml_oarchive archive(file);
	archive << boost::serialization::make_nvp("lights", framedata.lights);

	archive << boost::serialization::make_nvp("algorithm", *framedata.render_algorithm_);

	return 0;
}

int import_lights(std::string const& filename, FrameData & framedata)
{
	std::ifstream file(filename.c_str());
	if (!file)
		return -1;

	boost::archive::xml_iarchive archive(file);
	archive >> boost::serialization::make_nvp("lights", framedata.lights);

	archive >> boost::serialization::make_nvp("algorithm", *framedata.render_algorithm_);

	return 0;
}
