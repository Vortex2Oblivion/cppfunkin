#include "raylib-cpp.hpp"

#include "note.hpp"
#include "strumnote.hpp"
#include <iostream>

funkin::Note::Note(double strumTime, int lane, double speed, StrumNote *strum) : Sprite(0, 0)
{
    this->strumTime = strumTime;
    this->lane = lane;
    this->speed = speed;
    this->strum = strum;
}

funkin::Note::~Note()
{
}

void funkin::Note::update(double delta)
{
    Sprite::update(delta);
    position.x = strum->position.x;
    position.y = 50 + -0.45 * (songPos * 1000 - strumTime) * speed;
}