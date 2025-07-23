#include "strumnote.hpp"

strumnote::strumnote(double x, double y, int lane, bool player) : sprite(x, y)
{
    this->lane = lane;
    this->player = player;
}

strumnote::~strumnote()
{
}

void strumnote::setPosition()
{
    position.x += 100 * lane + 50 + (GetRenderWidth() / 2 * (player ? 0 : 1));
}