#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Shape.hpp"

class Line : public Shape
{
public:
  Line(const Point &, const Point &, const Color &);

  // Draw the line.
  void draw(SDL_Renderer *);
  ~Line();
};