#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include "Shape.hpp"

class Rect : public Shape
{
private:
  SDL_Rect m_fill_rect;

public:
  Rect(SDL_Rect, const Color &);

  // Draw the rectangle.
  void draw(SDL_Renderer *);
  ~Rect();
};
