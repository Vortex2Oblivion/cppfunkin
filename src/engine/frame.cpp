#include "frame.hpp"

#include <iostream>
#include <raylib-cpp.hpp>

engine::Frame::Frame(raylib::Rectangle rect) {
    this->x = rect.x;
    this->y = rect.y;
    this->width = rect.width;
    this->height = rect.height;
    this->frameX = rect.y;
    this->frameY = rect.x;
    this->frameWidth = rect.width;
    this->frameHeight = rect.height;

    exists = true;
}

engine::Frame::Frame(raylib::Rectangle rect, raylib::Vector2 sourceSize, raylib::Vector2 offset) {
    this->x = rect.x;
    this->y = rect.y;
    this->width = rect.width;
    this->height = rect.height;
    this->frameX = offset.x;
    this->frameY = offset.y;
    this->frameWidth = sourceSize.x;
    this->frameHeight = sourceSize.y;

    exists = true;
}

engine::Frame::Frame(float x, float y, float width, float height, float frameX, float frameY, float frameWidth, float frameHeight) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->frameX = frameX;
    this->frameY = frameY;
    this->frameWidth = frameWidth;
    this->frameHeight = frameHeight;

    exists = true;
}

engine::Frame::~Frame() { exists = false; }