#include "frame.hpp"
#include <raylib-cpp.hpp>


funkin::Frame::Frame(raylib::Rectangle rect)
{
}

funkin::Frame::Frame(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

funkin::Frame::~Frame()
{
}