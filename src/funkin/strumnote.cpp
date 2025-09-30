#include "strumnote.hpp"

funkin::StrumNote::StrumNote(float x, float y, int lane, bool player) : SparrowSprite(x, y)
{
    this->lane = lane;
    this->player = player;

    std::vector<std::string> directions = {"left", "down", "up", "right"};
    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");
    addAnimationByPrefix("press", directions[lane % 4] + " press", 24);
    addAnimationByPrefix("confirm", directions[lane % 4] + " confirm", 24);
    addAnimationByPrefix("static", directions[lane % 4] + " static", 24);
    playAnimation("static");
    scale.x = 0.7f;
    scale.y = 0.7f;
}

funkin::StrumNote::~StrumNote()
{
}

void funkin::StrumNote::setPosition()
{
    position.x += (160 * scale.x) * lane + 50 + (GetRenderWidth() / 2 * (player ? 1 : 0));
}