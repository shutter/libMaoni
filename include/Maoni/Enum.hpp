/*
 * libMaoni - common viewing framework
 *
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 * Visualization and Multimedia Lab, University of Zurich
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

#ifndef MAONI_ENUM_HPP
#define MAONI_ENUM_HPP

#define ENUM(NAME, VALUES)                                                     \
    class NAME: public Enum                                                    \
    {                                                                          \
    public:                                                                    \
        NAME(int value) :                                                      \
            Enum(value)                                                        \
        {                                                                      \
        }                                                                      \
                                                                               \
        enum                                                                   \
        {                                                                      \
            BOOST_PP_SEQ_ENUM(VALUES)                                          \
        };                                                                     \
                                                                               \
    private:                                                                   \
        int size() const                                                       \
        {                                                                      \
   	        return BOOST_PP_SEQ_SIZE(VALUES);                                  \
        }                                                                      \
                                                                               \
        const char* const * names() const                                      \
        {                                                                      \
            static const char* const name_stack[] =                            \
                { BOOST_PP_SEQ_FOR_EACH(COMMA_SEP_STRINGS,, VALUES) 0 };       \
            return name_stack;                                                 \
        }                                                                      \
    }                                                                          \

#include <Maoni/detail/Enum.hpp>

#endif /* MAONI_ENUM_HPP */
