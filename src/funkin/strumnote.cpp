#include "strumnote.hpp"
#include "raylib.h"

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
    //engine::SparrowSprite::~SparrowSprite();
}

void funkin::StrumNote::setPosition()
{
    position.x += (160.0f * scale.x) * lane + 50.0f;
}
