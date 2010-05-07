/*
 * RenderAlgorithm.hpp
 *
 *  Created on: Jul 22, 2009
 *      Author: dpfeifer
 */

#ifndef VMMVIEW_COMMON_RENDER_ALGORITHM_HPP
#define VMMVIEW_COMMON_RENDER_ALGORITHM_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <Maoni/Color.hpp>
#include <Maoni/Model.hpp>
#include <Maoni/detail/Extensible.hpp>
#include <Maoni/detail/ShaderProgram.hpp>

class Enum;
class Texture;

struct AlgorithmConfig
{
	virtual void property(const char* name, int& value) = 0;
	virtual void property(const char* name, bool& value) = 0;
	virtual void property(const char* name, float& value) = 0;
	virtual void property(const char* name, double& value) = 0;
	virtual void property(const char* name, Enum& value) = 0;
	virtual void property(const char* name, Color& value) = 0;
	virtual void property(const char* name, Texture& value) = 0;
	virtual void property(const char* name, ShaderProgram& value) = 0;
};

struct Algorithm: boost::noncopyable
{
	typedef boost::shared_ptr<Algorithm> Ptr;

	virtual const char* name() const = 0;
	virtual void render(const Model& model) const = 0;
	//virtual void config(AlgorithmConfig& algo_config) = 0;
};

struct AlgoConfig: boost::noncopyable
{
	typedef boost::shared_ptr<AlgoConfig> Ptr;

	virtual const char* name() const = 0;
	virtual void config(AlgorithmConfig& algo_config) = 0;
};

struct AlgorithmFactory: Extensible<AlgorithmFactory>
{
	static AlgoConfig::Ptr create_config(const std::string& name)
	{
		for (AlgorithmFactory* i = stack; i; i = i->next)
		{
			if (name == i->name())
				return i->config();
		}
		return AlgoConfig::Ptr();
	}

	virtual const char* name() const = 0;
	virtual Algorithm::Ptr algorithm() = 0;
	virtual AlgoConfig::Ptr config() = 0;
};

#endif /* VMMVIEW_COMMON_RENDER_ALGORITHM_HPP */
