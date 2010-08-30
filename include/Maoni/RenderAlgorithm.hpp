/*
 * libMaoni - common viewing framework
 *
 * Copyright (C) 2009, 2010 Daniel Pfeifer, Stefan Hutter
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

#ifndef MAONI_RENDER_ALGORITHM_HPP
#define MAONI_RENDER_ALGORITHM_HPP

#include <Maoni/detail/Extensible.hpp>
#include <Maoni/Model.hpp>

class Enum;
class Path;
class Color;
class ShaderProgram;

/**
 * \brief Public interface for render algorithm properties
 *
 * To map the changeable properties of an algorithm (defined in the
 * BSEQ property list), a responsible GUI class has to implement this
 * interface and call the config() method.
 * E.g. the AlgorithmWidget implements this interface to pass
 * changes in the render algorithms property tree to the render
 * algorithm itself.
 */
struct AlgorithmConfig
{
	//! Method to map an algorithm's integer variables to a GUI element
    /*!
      \param name Property name
      \param value Reference to an integer affected by the property
    */
	virtual void property(const char* name, int& value) = 0;

	//! Method to map an algorithm's boolean variables to a GUI element
    /*!
      \param name Property name
      \param value Reference to a boolean affected by the property
    */
	virtual void property(const char* name, bool& value) = 0;

	//! Method to map an algorithm's float variables to a GUI element
    /*!
      \param name Property name
      \param value Reference to a float affected by the property
    */
	virtual void property(const char* name, float& value) = 0;

	//! Signature of a method to map an algorithm's double variables to a GUI element
    /*!
      \param name Property name
      \param value Reference to a double affected by the property
    */
	virtual void property(const char* name, double& value) = 0;

	//! Signature of a method to map an algorithm's enumerators to a GUI element
    /*!
      \param name Property name
      \param value Reference to an enumerator affected by the property
    */
	virtual void property(const char* name, Enum& value) = 0;

	//! Signature of a method to map an algorithm's path objects to a GUI element
    /*!
      \param name Property name
      \param value Reference to the path object affected by the property
    */
	virtual void property(const char* name, Path& value) = 0;

	//! Signature of a method to map an algorithm's color objects to a GUI element
    /*!
      \param name Property name
      \param value Reference to the color object affected by the property
    */
	virtual void property(const char* name, Color& value) = 0;

	//! Signature of a method to map an algorithm's shader program
    /*!
      \param name Property name
      \param value Reference to the shader program affected by the property
    */
	virtual void property(const char* name, ShaderProgram& value) = 0;
};

/**
 * \brief Base class RenderAlgorithm
 *
 * Defines the public interface for any render algorithm using the
 * RENDER_ALGORITHM macro. The methods name() and config() are
 * created by the macro automatically and are used by the AlgorithmWidget
 * to make the algorithm selectable and populate the property tree.
 * The render() method has to be implemented by yourself and defines what
 * will be done in every drawing loop.
 *
 * RENDER_ALGORITHM(name, properties){algorithm stub}
 */
struct RenderAlgorithm: Extensible<RenderAlgorithm>
{
	//! Signature of a method which returns a render algorithms name
    /*!
      \return A const pointer to the render algorithm's name
    */
	virtual const char* name() const = 0;

	//! Signature of the method called every drawing loop
    /*!
      \param model A const reference to the model to be drawn by
      the render algorithm
    */
	virtual void render(const Model& model) const = 0;

	/** Signature of a method which maps the render algorithm's parameter
	 *  list to a GUI using the property methods of the AlgorithmConfig interface
	 *
	 *  \param algo_config A const reference to a class which has the AlgorithmConfig interface implemented
	 */
	virtual void config(AlgorithmConfig& algo_config) = 0;
};

/**
 * \brief Define a custom render algorithm.
 *
 * Extends the algorithm name and its GUI controlled variables to a
 * RenderAlgorithm subclass, which will be linked against libMaoni.
 * The macro ensures the right interface to make the algorithm available
 * in the drop down menu of the render algorithm widget.
 * Have a look at the RenderAlgorithm-tutorial and algorithm examples for
 * information about concrete implementation.
 *
 * \param NAME The name of this algorithm.
 * \param BSEQ A sequence of parameters. Each parameter has the form
 * (type, value, default)
 */
#define RENDER_ALGORITHM(NAME, BSEQ) \
    RENDER_ALGORITHM_I(NAME, BOOST_PP_CAT(RENDER_ALGORITHM_X BSEQ, 0))

#include <Maoni/detail/Algorithm_PP.hpp>

#endif /* MAONI_RENDER_ALGORITHM_HPP */
