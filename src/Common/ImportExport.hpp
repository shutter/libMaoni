/*
 * ImportExport.hpp
 *
 *  Created on: 08.04.2010
 *      Author: daniel
 */

#ifndef IMPORTEXPORT_HPP
#define IMPORTEXPORT_HPP

#include <string>

class FrameData;

int export_lights(std::string const& filename, FrameData const& framedata);
int import_lights(std::string const& filename, FrameData & framedata);

#endif /* IMPORTEXPORT_HPP */
