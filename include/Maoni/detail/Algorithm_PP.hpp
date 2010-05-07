/*
 * VMMView.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#ifndef MAONI_DETAIL_ALGORITHM_PP_HPP
#define MAONI_DETAIL_ALGORITHM_PP_HPP

#include <boost/preprocessor/cat.hpp>
#include <Maoni/detail/Algorithm.hpp>
#include <Maoni/detail/Algorithm_PP_Simple.hpp>

#define RENDER_ALGORITHM_X(T, V, D) ((T, V, D)) RENDER_ALGORITHM_Y
#define RENDER_ALGORITHM_Y(T, V, D) ((T, V, D)) RENDER_ALGORITHM_X
#define RENDER_ALGORITHM_X0
#define RENDER_ALGORITHM_Y0

#define RENDER_ALGORITHM_I(NAME, SEQ)                                          \
                                                                               \
	class NAME: public AlgorithmFactory                                        \
	{                                                                          \
		struct Algo: ALGORITHM_BASE(Algorithm)                                 \
		{                                                                      \
			ALGORITHM_CTOR(Algo, SEQ)                                          \
			ALGORITHM_DIRT_FLAGS(SEQ)                                          \
			ALGORITHM_DESERIALIZE(SEQ)                                         \
			ALGORITHM_MEMBER(SEQ)                                              \
                                                                               \
			const char* name() const { return #NAME; }                         \
			void render(const Model& model) const;                             \
		};                                                                     \
                                                                               \
		struct Config: ALGORITHM_BASE(AlgoConfig)                              \
		{                                                                      \
			ALGOCONFIG_CTOR(Config, SEQ)                                       \
			ALGORITHM_DIRT_FLAGS(SEQ)                                          \
			ALGORITHM_SERIALIZE(SEQ)                                           \
			ALGORITHM_MEMBER(SEQ)                                              \
			ALGORITHM_SETTERS(SEQ)                                             \
                                                                               \
			const char* name() const { return #NAME; }                         \
			void config(AlgorithmConfig& manager)                              \
			{                                                                  \
				ALGORITHM_ADD_PROPERTIES(SEQ)                                  \
			}                                                                  \
		};                                                                     \
                                                                               \
	public:                                                                    \
        ALGORITHM_FACTORY_CTOR(NAME, SEQ)                                      \
                                                                               \
		const char* name() const { return #NAME; }                             \
                                                                               \
		Algorithm::Ptr algorithm()                                             \
		{                                                                      \
			return Algorithm::Ptr(new Algo(ALGORITHM_PARAMETERS(SEQ)));        \
		}                                                                      \
                                                                               \
		AlgoConfig::Ptr config()                                               \
		{                                                                      \
			return AlgoConfig::Ptr(new Config(ALGORITHM_PARAMETERS(SEQ)));     \
		}                                                                      \
                                                                               \
	private:                                                                   \
		ALGORITHM_FACTORY_MEMBER(SEQ)                                          \
                                                                               \
		static NAME instance;                                                  \
	};                                                                         \
                                                                               \
	NAME NAME::instance;                                                       \
	void NAME::Algo::render(const Model& model) const                          \

#endif /* MAONI_DETAIL_ALGORITHM_PP_HPP */
