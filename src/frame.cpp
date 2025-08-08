#include "frame.hpp"
#include <raylib-cpp.hpp>

funkin::Frame::Frame(float x, float y, float width, float height, float frameX, float frameY, float frameWidth, float frameHeight)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->frameX = frameX;
    this->frameY = frameY;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;
}

funkin::Frame::~Frame()
{
}