#include "frame.hpp"
#include <raylib-cpp.hpp>


funkin::Frame::Frame(raylib::Rectangle rect)
{
}

funkin::Frame::Frame(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

funkin::Frame::~Frame()
{
}