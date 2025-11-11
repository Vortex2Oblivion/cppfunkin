#include "note.hpp"

#include "raylib-cpp.hpp"

#include <array>

funkin::Note::Note(const float strumTime, const int lane, const float speed) : SparrowSprite(0, 0) {
    this->strumTime = strumTime;
    this->lane = lane;
    this->speed = speed;

    const std::array<std::string, 4> directions = {"purple", "blue", "green", "red"};

    const std::string& direction = directions[lane % 4];

    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");
    addAnimation("default", direction + " instance", 24);
    addAnimation("hold", direction + " hold piece instance", 24);
    addAnimation("hold_end", direction + " hold end instance", 24);
    playAnimation("default");

    scale.x = 0.7f;
    scale.y = 0.7f;
    position.y += 2000;
}

funkin::Note::~Note() = default;

void funkin::Note::update(const float delta) { SparrowSprite::update(delta); }

void funkin::Note::updateY(const float songPosition) { position.y = 50 + -0.45f * (songPosition - strumTime) * speed; }

void funkin::Note::draw(const float x, const float y) {
    const bool shouldScissor = isSustain && (laneHeld || wasHit || isQueuedSustain);
    if (shouldScissor) {
        // replace the magic number with an actual strum y someday probably !!!
        // lol!!!
         const int yScissor = static_cast<int>(camera->GetWorldToScreen({0.0, 125.0}).y);
        BeginScissorMode(0, yScissor, 1280, 720-yScissor);
    }

    engine::SparrowSprite::draw(x, y);

    if (shouldScissor) {
        EndScissorMode();
    }
}