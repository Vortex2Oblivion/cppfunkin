#include "note.hpp"

#include "raylib-cpp.hpp"
#include "strumnote.hpp"

funkin::Note::Note(float strumTime, int lane, float speed, StrumNote* strum) : SparrowSprite(0, 0) {
    this->strumTime = strumTime;
    this->lane = lane;
    this->speed = speed;
    this->strum = strum;

    std::vector<std::string> directions = {"purple", "blue", "green", "red"};
    loadGraphic("assets/images/notes.png", "assets/images/notes.xml");
    addAnimation("default", directions[lane % 4] + " instance", 24);
    playAnimation("default");
    scale.x = 0.7f;
    scale.y = 0.7f;
    position.y += 2000;
    position.x = strum->position.x;
}

funkin::Note::~Note() {}

void funkin::Note::update(float delta) {
    SparrowSprite::update(delta);
    position.y = 50 + -0.45f * (songPos * 1000 - strumTime) * speed;
}
