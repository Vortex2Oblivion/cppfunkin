#include "strumnote.hpp"

#include "raylib.h"

#include <array>

funkin::StrumNote::StrumNote(float x, float y, int lane, bool player) : SparrowSprite(x, y) {
    this->lane = lane;
    this->player = player;

    const std::array<std::string, 4> directions = {"left", "down", "up", "right"};

    const std::string direction = std::move(directions[lane % 4]);

    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");

    addAnimation("press", direction + " press", 24);
    addAnimation("confirm", direction + " confirm", 24);
    addAnimation("static", direction + " static", 24);

    playAnimation("static");

    scale = raylib::Vector2(0.7f, 0.7f);
}

funkin::StrumNote::~StrumNote() = default;
void funkin::StrumNote::setPosition() { position.x += (160.0f * scale.x) * static_cast<float>(lane) + 50.0f; }
