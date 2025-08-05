#include "strumnote.hpp"

funkin::StrumNote::StrumNote(double x, double y, int lane, bool player) : Sprite(x, y)
{
    this->lane = lane;
    this->player = player;
}

funkin::StrumNote::~StrumNote()
{
}

void funkin::StrumNote::setPosition()
{
    position.x += 100 * lane + 50 + (GetRenderWidth() / 2 * (player ? 0 : 1));
}