/*
 * Algorithm_PP_Simple.hpp
 *
 *  Created on: 07.12.2009
 *      Author: daniel
 */

#ifndef ALGORITHM_PP_SIMPLE_HPP
#define ALGORITHM_PP_SIMPLE_HPP

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
//#include <boost/bind.hpp>

#define ALGO_TYP(TVD) BOOST_PP_TUPLE_ELEM(3, 0, TVD)
#define ALGO_VAL(TVD) BOOST_PP_TUPLE_ELEM(3, 1, TVD)
#define ALGO_DEF(TVD) BOOST_PP_TUPLE_ELEM(3, 2, TVD)

// inherit from BASE only
#define ALGORITHM_BASE(BASE) BASE

// only used by equalizer
#define ALGORITHM_DIRT_FLAGS(X)
#define ALGORITHM_DESERIALIZE(X)
#define ALGORITHM_SERIALIZE(X)

#define COLON() :

#define ALGORITHM_CTOR_P(r, data, i, elem)                                     \
   BOOST_PP_COMMA_IF(i)                                                        \
   ALGO_TYP(elem) & BOOST_PP_CAT(ALGO_VAL(elem), _)                            \

#define ALGORITHM_CTOR_I(r, data, i, elem)                                     \
   BOOST_PP_IF(i, BOOST_PP_COMMA, COLON)()                                     \
   ALGO_VAL(elem) ( BOOST_PP_CAT(ALGO_VAL(elem), _) )                          \

//
#define ALGORITHM_CTOR(NAME, SEQ)                                              \
   NAME(BOOST_PP_SEQ_FOR_EACH_I(ALGORITHM_CTOR_P,, SEQ))                       \
   BOOST_PP_SEQ_FOR_EACH_I(ALGORITHM_CTOR_I,, SEQ) {}                          \

// simple: same as algorithm ctor
#define ALGOCONFIG_CTOR ALGORITHM_CTOR                                         \

// helper for ALGORITHM_FACTORY_CTOR
#define ALGORITHM_FACTORY_CTOR_I(r, data, i, elem)                             \
   BOOST_PP_IF(i, BOOST_PP_COMMA, COLON)()                                     \
   ALGO_VAL(elem) ( ALGO_DEF(elem) )                                           \

// : v0(d0), v1(d1), ...
#define ALGORITHM_FACTORY_CTOR(NAME, SEQ)                                      \
   NAME() BOOST_PP_SEQ_FOR_EACH_I(ALGORITHM_FACTORY_CTOR_I,, SEQ) {}           \

// helper for ALGORITHM_MEMBER and ALGORITHM_FACTORY_MEMBER
#define ALGORITHM_MEMBER_I(r, data, elem)                                      \
   ALGO_TYP(elem) data ALGO_VAL(elem) ;                                        \

// references
#define ALGORITHM_MEMBER(SEQ)                                                  \
   BOOST_PP_SEQ_FOR_EACH(ALGORITHM_MEMBER_I, &, SEQ)                           \

#define ALGORITHM_SETTERS_I(r, data, elem)                                     \
   void BOOST_PP_CAT(set_, ALGO_VAL(elem))(ALGO_TYP(elem) const& value)        \
   { this->ALGO_VAL(elem) = value; }                                           \

#define ALGORITHM_SETTERS(SEQ)                                                 \
   BOOST_PP_SEQ_FOR_EACH(ALGORITHM_SETTERS_I,, SEQ)                            \

// factory has values
#define ALGORITHM_FACTORY_MEMBER(SEQ)                                          \
   BOOST_PP_SEQ_FOR_EACH(ALGORITHM_MEMBER_I,, SEQ)                             \

#define ALGORITHM_PARAMETERS_I(r, data, i, elem)                               \
   BOOST_PP_COMMA_IF(i) ALGO_VAL(elem)                                         \

#define ALGORITHM_PARAMETERS(SEQ)                                              \
   BOOST_PP_SEQ_FOR_EACH_I(ALGORITHM_PARAMETERS_I,, SEQ)                       \

//
#define ALGORITHM_ADD_PROPERTIES_I(r, data, elem)                              \
   manager.property(BOOST_PP_STRINGIZE(ALGO_VAL(elem)), ALGO_VAL(elem));       \

//   boost::bind(&Config::BOOST_PP_CAT(set_, ALGO_VAL(elem)), this, _1),
///* ALGO_TYP(elem)(ALGO_DEF(elem))); */
//   ALGO_VAL(elem));

#define ALGORITHM_ADD_PROPERTIES(SEQ)                                          \
   BOOST_PP_SEQ_FOR_EACH(ALGORITHM_ADD_PROPERTIES_I,, SEQ)                     \

#endif /* ALGORITHM_PP_SIMPLE_HPP */

