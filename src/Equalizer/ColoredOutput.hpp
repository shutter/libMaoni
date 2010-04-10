/*
 * Channel.hpp
 *
 *  Created on: 31.07.2009
 *      Author: daniel
 */

#ifndef COLORED_OUTPUT_HPP
#define COLORED_OUTPUT_HPP

# ifndef WIN32
#   define RED(X) "\e[0;32m" << X << "\e[m"
# else
#   define RED(X) X
# endif

#endif /* COLORED_OUTPUT_HPP */
