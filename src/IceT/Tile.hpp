/*
 * Tile.hpp
 *
 *  Created on: Mar 25 2009
 *      Author: stefan
 */

#ifndef TILE_HPP
#define TILE_HPP

#include <Maoni/Vector.hpp>
#include <string>

class Tile
{
public:
	Tile() :
		name("Tile"), x(0), y(0), width(0), height(0), display_rank(0), is_active(false)
	{
	}

private:
	std::string name;
	int x;
	int y;
	int width;
	int height;
	int display_rank;
	bool is_active;

public:
    int getDisplay_rank() const
    {
        return display_rank;
    }

    int getHeight() const
    {
        return height;
    }

    bool getIs_active() const
    {
        return is_active;
    }

    std::string getName() const
    {
        return name;
    }

    int getWidth() const
    {
        return width;
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    void setDisplay_rank(int display_rank)
    {
        this->display_rank = display_rank;
    }

    void setHeight(int height)
    {
        this->height = height;
    }

    void setIs_active(bool is_active)
    {
        this->is_active = is_active;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    void setWidth(int width)
    {
        this->width = width;
    }

    void setX(int x)
    {
        this->x = x;
    }

    void setY(int y)
    {
        this->y = y;
    }

};

#endif /* TILE_HPP */
