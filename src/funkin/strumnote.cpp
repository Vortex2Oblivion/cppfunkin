#include "strumnote.hpp"
#include <array>

funkin::StrumNote::StrumNote(const float x, const float y, const int lane) : engine::SparrowSprite(x, y) {
    this->lane = lane;

    const std::array<std::string, 4> directions = {"left", "down", "up", "right"};

    const std::string& direction = directions[lane % 4];

    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");

    addAnimation("press", direction + " press", 24);
    addAnimation("confirm", direction + " confirm", 24);
    addAnimation("static", direction + " static", 24);

    playAnimation("static");

    scale = raylib::Vector2(0.7f, 0.7f);
}

funkin::StrumNote::~StrumNote() = default;
void funkin::StrumNote::setPosition() { position.x += (160.0f * scale.x) * static_cast<float>(lane) + 50.0f; }
