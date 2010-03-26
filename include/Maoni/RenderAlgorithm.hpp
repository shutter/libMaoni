/*
 * VMMView.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#ifndef MAONI_RENDER_ALGORITHM_HPP
#define MAONI_RENDER_ALGORITHM_HPP

/**
 * Define a custom render algorithm.
 *
 * Some description on how to use this macro.
 *
 * \param NAME The name of this algorithm.
 * \param BSEQ A sequence of parameters. Each parameter has the form
 * (type, value, default)
 */
#define RENDER_ALGORITHM(NAME, BSEQ) \
    RENDER_ALGORITHM_I(NAME, BOOST_PP_CAT(RENDER_ALGORITHM_X BSEQ, 0))

#include <Maoni/detail/Algorithm_PP.hpp>

#endif /* MAONI_RENDER_ALGORITHM_HPP */
