/*
 * Extensible.hpp
 *
 *  Created on: 30.07.2009
 *      Author: daniel
 */

#ifndef VMMVIEW_COMMON_EXTENSIBLE_HPP
#define VMMVIEW_COMMON_EXTENSIBLE_HPP

template<typename CR>
struct Extensible
{
	Extensible()
	{
		next = stack;
		stack = static_cast<CR*> (this);
	}

//protected:
	static CR* stack;
	CR* next;
};

template<typename CR>
CR* Extensible<CR>::stack = 0;

#endif /* VMMVIEW_COMMON_EXTENSIBLE_HPP */
