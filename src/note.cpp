#include "raylib-cpp.hpp"

#include "note.hpp"
#include "strumnote.hpp"
#include <iostream>

note::note(double strumTime, int lane, double speed, strumnote *strum) : sprite(0, 0)
{
    this->strumTime = strumTime;
    this->lane = lane;
    this->speed = speed;
    this->strum = strum;
}

note::~note()
{
}

void note::update(double delta)
{
    sprite::update(delta);
    position.x = strum->position.x;
    position.y = 50 + -0.45 * (songPos * 1000 - strumTime) * speed;
}