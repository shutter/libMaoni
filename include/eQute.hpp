/*
 * eQute - extremely qualified universal toolkit experiment
 *
 * Copyright (C) 2010 Daniel Pfeifer, University of Zurich
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EQUTE_HPP_INCLUDED
#define EQUTE_HPP_INCLUDED

#include <eq/eq.h>

template<typename Widget>
struct eQute
{
	class WidgetBase
	{
	public:
		WidgetBase()
		{
			instance = static_cast<Widget*> (this);
			instance.data->doneCurrent();
		}

		static Widget* getInstance()
		{
			eq::base::ScopedMutex<> lock(instance);

			Widget* tmp = instance.data;
			instance = 0;
			return tmp;
		}

	private:
		static eq::base::Lockable<Widget*> instance;
	};

	class GLWindow: public eq::GLWindow
	{
	public:
		GLWindow(eq::Window* window, Widget* widget) :
			eq::GLWindow(window), widget(widget)
		{
			makeCurrent();
			initGLEW();
		}

		Widget* getWidget() const
		{
			return widget;
		}

	private:
		bool configInit()
		{
			return true;
		}

		void configExit()
		{
		}

		void makeCurrent() const
		{
			widget->makeCurrent();
		}

		void swapBuffers()
		{
			widget->swapBuffers();
		}

		void joinNVSwapBarrier(uint32_t, uint32_t)
		{
		}

	private:
		Widget* widget;
	};

	class Window: public eq::Window
	{
	public:
		Window(eq::Pipe* pipe) :
			eq::Window(pipe)
		{
		}

	private:
		bool configInitOSWindow(const uint32_t id)
		{
			Widget* widget = Widget::getInstance();

			if (!widget)
			{
				// Share context only between Eq-created OS windows
				eq::OSWindow* osWindow = getSharedContextWindow()->getOSWindow();
				if (dynamic_cast<GLWindow*> (osWindow))
				{
					const std::vector<eq::Window*>& windows = getPipe()->getWindows();
					EQASSERT( windows.size() > 1 );
					setSharedContextWindow(windows[1]);
				}

				return eq::Window::configInitOSWindow(id);
			}

			setOSWindow(new GLWindow(this, widget));
			return true;
		}
	};

	class Channel: public eq::Channel
	{
	public:
		Channel(eq::Window* window) :
			eq::Channel(window)
		{
		}

	private:
		void frameDraw(const uint32_t id)
		{
			eq::Channel::frameDraw(id);

			GLWindow* glwindow =
					dynamic_cast<GLWindow*> (getWindow()->getOSWindow());

			if (glwindow)
				glwindow->getWidget()->paintGL();
			else
				Widget::static_draw(this);
		}
	};

	class Factory: public eq::NodeFactory
	{
		eq::Window* createWindow(eq::Pipe* pipe)
		{
			return new Window(pipe);
		}

		eq::Channel* createChannel(eq::Window* window)
		{
			return new Channel(window);
		}
	};
};

template<typename Widget>
eq::base::Lockable<Widget*> eQute<Widget>::WidgetBase::instance;

#endif /* EQUTE_HPP_INCLUDED */
