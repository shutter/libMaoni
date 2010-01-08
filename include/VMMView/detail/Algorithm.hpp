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
#include <boost/function.hpp>

#include <VMMView/Color.hpp>
#include <VMMView/Model.hpp>
#include <VMMView/detail/Extensible.hpp>
#include <VMMView/detail/ShaderProgram.hpp>

struct Algorithm: boost::noncopyable
{
	typedef boost::shared_ptr<Algorithm> Ptr;

	virtual const char* name() const = 0;
	virtual void render(const Model& model) const = 0;
};

struct AlgoConfigManager
{
	typedef boost::function<void(int const&)> int_setter;
	typedef boost::function<void(bool const&)> bool_setter;
	typedef boost::function<void(float const&)> float_setter;
	typedef boost::function<void(double const&)> double_setter;
	typedef boost::function<void(Color const&)> color_setter;
	typedef boost::function<void(std::string const&)> string_setter;

	virtual void add_property(const char* name, int_setter func, int def) = 0;
	virtual void add_property(const char* name, bool_setter func, bool def) = 0;
	virtual void add_property(const char* name, float_setter func, float def) = 0;
	virtual void add_property(const char* name, double_setter func, double def) = 0;
	virtual void add_property(const char* name, color_setter func, Color const& def) = 0;
	virtual void add_property(const char* name, string_setter func, std::string const& def) = 0;

	// reserved for later use
	typedef boost::function<void(ShaderProgram const&)> shader_setter;
	void add_property(const char*, shader_setter, ShaderProgram const&)
	{
	}
};

struct AlgoConfig: boost::noncopyable
{
	typedef boost::shared_ptr<AlgoConfig> Ptr;

	virtual const char* name() const = 0;
	virtual void config(AlgoConfigManager& manager) = 0;
};

struct AlgorithmFactory: Extensible<AlgorithmFactory>
{
	static Algorithm::Ptr create(const std::string& name)
	{
		for (AlgorithmFactory* i = stack; i; i = i->next)
		{
			if (name == i->name())
				return i->algorithm();
		}
		return Algorithm::Ptr();
	}

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
