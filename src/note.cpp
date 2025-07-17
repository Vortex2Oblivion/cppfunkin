#include "raylib-cpp.hpp"

#include "note.hpp"
#include <iostream>

note::note(double strumTime, int lane, double speed) : sprite(0, 0)
{
    this->strumTime = strumTime;
    this->lane = lane;
    this->speed = speed;
}

note::~note()
{
}

void note::update(double delta)
{
    sprite::update(delta);
    position.x = 100 * lane;
    position.y = -0.45 * (songPos * 1000 - strumTime) * speed;
}