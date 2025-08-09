#include "strumnote.hpp"

funkin::StrumNote::StrumNote(double x, double y, int lane, bool player) : SparrowSprite(x, y)
{
    this->lane = lane;
    this->player = player;

    std::vector<std::string> directions = {"left", "down", "up", "right"};
    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");
    addAnimationByPrefix("confirm", directions[lane % 4] + " confirm", 24);
    addAnimationByPrefix("static", directions[lane % 4] + " static", 24);
    playAnimation("static");
    scale.x = 0.7;
    scale.y = 0.7;
}

funkin::StrumNote::~StrumNote()
{
}

void funkin::StrumNote::setPosition()
{
    position.x += (160 * scale.x) * lane + 50 + (GetRenderWidth() / 2 * (player ? 0 : 1));
}