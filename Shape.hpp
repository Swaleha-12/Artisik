#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Point.hpp"
#include "Color.hpp"
#include <iostream>

class Shape
{
protected:
	Color m_color;
	Point m_top_left;
	Point m_bottom_right;

public:
	//Draw Shape
	virtual void draw(SDL_Renderer *) = 0;
	virtual ~Shape()
	{
		std::cout << "Shape::~Shape()\n";
	}
};