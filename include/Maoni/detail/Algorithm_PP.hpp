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

#ifndef MAONI_DETAIL_ALGORITHM_PP_HPP
#define MAONI_DETAIL_ALGORITHM_PP_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define RENDER_ALGORITHM_X(T, V, D) ((T, V, D)) RENDER_ALGORITHM_Y
#define RENDER_ALGORITHM_Y(T, V, D) ((T, V, D)) RENDER_ALGORITHM_X
#define RENDER_ALGORITHM_X0
#define RENDER_ALGORITHM_Y0

#define RENDER_ALGORITHM_I(NAME, SEQ)                                          \
                                                                               \
	class NAME: public RenderAlgorithm                                         \
	{                                                                          \
	public:                                                                    \
        NAME() BOOST_PP_SEQ_FOR_EACH_I(ALGORITHM_CTOR_I,, SEQ) {}              \
                                                                               \
		const char* name() const { return #NAME; }                             \
                                                                               \
        void render(const Model& model) const;                                 \
                                                                               \
		void config(AlgorithmConfig& manager)                                  \
		{                                                                      \
			BOOST_PP_SEQ_FOR_EACH(ALGORITHM_PROPERTIES_I,, SEQ)                \
		}                                                                      \
                                                                               \
	private:                                                                   \
		BOOST_PP_SEQ_FOR_EACH(ALGORITHM_MEMBER_I,, SEQ)                        \
                                                                               \
		static NAME instance;                                                  \
	};                                                                         \
                                                                               \
	NAME NAME::instance;                                                       \
	void NAME::render(const Model& model) const                                \

#define COLON() :

#define ALGO_TYP(TVD) BOOST_PP_TUPLE_ELEM(3, 0, TVD)
#define ALGO_VAL(TVD) BOOST_PP_TUPLE_ELEM(3, 1, TVD)
#define ALGO_DEF(TVD) BOOST_PP_TUPLE_ELEM(3, 2, TVD)

#define ALGORITHM_CTOR_I(r, data, i, elem)                                     \
   BOOST_PP_IF(i, BOOST_PP_COMMA, COLON)() ALGO_VAL(elem)(ALGO_DEF(elem))      \

#define ALGORITHM_PROPERTIES_I(r, data, elem)                                  \
   manager.property(BOOST_PP_STRINGIZE(ALGO_VAL(elem)), ALGO_VAL(elem));       \

#define ALGORITHM_MEMBER_I(r, data, elem) ALGO_TYP(elem) ALGO_VAL(elem);       \

#endif /* MAONI_DETAIL_ALGORITHM_PP_HPP */
