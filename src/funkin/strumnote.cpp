#include "strumnote.hpp"

#include "raylib.h"

funkin::StrumNote::StrumNote(float x, float y, int lane, bool player) : SparrowSprite(x, y) {
    this->lane = lane;
    this->player = player;

    const std::vector<std::string> directions = {"left", "down", "up", "right"};
    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");
    addAnimation("press", directions[lane % 4] + " press", 24);
    addAnimation("confirm", directions[lane % 4] + " confirm", 24);
    addAnimation("static", directions[lane % 4] + " static", 24);
    playAnimation("static");
    scale.x = 0.7f;
    scale.y = 0.7f;
}

funkin::StrumNote::~StrumNote() = default;
void funkin::StrumNote::setPosition() { position.x += (160.0f * scale.x) * static_cast<float>(lane) + 50.0f; }
