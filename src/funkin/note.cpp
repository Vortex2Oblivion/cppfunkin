#include "note.hpp"

#include "raylib-cpp.hpp"

funkin::Note::Note(float strumTime, int lane, float speed) : SparrowSprite(0, 0) {
    this->strumTime = strumTime;
    this->lane = lane;
    this->speed = speed;

    std::vector<std::string> directions = {"purple", "blue", "green", "red"};
    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");
    addAnimation("default", directions[lane % 4] + " instance", 24);
    addAnimation("hold", directions[lane % 4] + " hold piece instance", 24);
    addAnimation("hold_end", directions[lane % 4] + " hold end instance", 24);
    playAnimation("default");
    scale.x = 0.7f;
    scale.y = 0.7f;
    position.y += 2000;
}

funkin::Note::~Note() {}

void funkin::Note::update(float delta) { SparrowSprite::update(delta); }

void funkin::Note::updateY(float songPosition) { position.y = 50 + -0.45f * (songPosition * 1000 - strumTime) * speed; }