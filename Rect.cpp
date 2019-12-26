#include "Rect.hpp"
#include <iostream>

Rect::Rect(SDL_Rect rect, const Color &color)
{
  m_fill_rect = rect;
  m_color = color;
}

void Rect::draw(SDL_Renderer *gRenderer)
{
  SDL_SetRenderDrawColor(gRenderer, m_color.m_red, m_color.m_green, m_color.m_blue, 0xFF);
  SDL_RenderFillRect(gRenderer, &m_fill_rect);
}

Rect::~Rect()
{
  std::cout << "Rect::~Rect()\n";
}