#include "Line.hpp"
#include <iostream>

Line::Line(const Point &topLeft, const Point &bottomRight, const Color &color)
{
    m_top_left = topLeft;
    m_bottom_right = bottomRight;
    m_color = color;
}

void Line::draw(SDL_Renderer *gRenderer)
{
    SDL_SetRenderDrawColor(gRenderer, m_color.m_red, m_color.m_green, m_color.m_blue, 0xFF);
    SDL_RenderDrawLine(gRenderer, m_top_left.m_x, m_top_left.m_y, m_bottom_right.m_x, m_bottom_right.m_y);
}

Line::~Line()
{
    std::cout << "Line::~Line()\n";
}