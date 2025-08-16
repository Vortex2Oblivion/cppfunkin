#include "frame.hpp"
#include <raylib-cpp.hpp>

funkin::Frame::Frame(raylib::Rectangle rect, raylib::Vector2 sourceSize, raylib::Vector2 offset)
{
    this->x = rect.x;
    this->y = rect.y;
    this->width = rect.width;
    this->height = rect.height;
    this->frameX = offset.x;
    this->frameY = offset.y;
    this->frameWidth = sourceSize.x;
    this->frameHeight = sourceSize.y;
}

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