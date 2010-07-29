/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
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

#ifndef LOGO_HPP_
#define LOGO_HPP_

#include <string>
#include <Maoni/Texture.hpp>

class Logo
{
public:
	Logo() :
		texture(":/Maoni/libmaoni_logo.png"), render(false)
	{
	}

	void set_path(const std::string path)
	{
		texture.path(path);
		calc_pos(window_width, window_height);
	}

	std::string get_path() const
	{
		return texture.path();
	}

	void set_render(bool render)
	{
		this->render = render;
	}

	bool get_render() const
	{
		return render;
	}

	void draw() const;

	void calc_pos(int window_width, int window_height);

private:
	bool render;
	Texture texture;
	int pos_x1, pos_x2, pos_y1, pos_y2;
	int window_width, window_height;
};

#endif /* LOGO_HPP_ */
