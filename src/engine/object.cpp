#include "object.hpp"

#include "game.hpp"

int engine::Object::instances = 0;

engine::Object::Object(const float x, const float y) {
    position = raylib::Vector2(x, y);
    scrollFactor = raylib::Vector2::One();
    camera = engine::Game::defaultCamera;
    instances++;
}
engine::Object::~Object() {
    alive = false;
    instances --;
}

void engine::Object::update(const float delta) {}

void engine::Object::draw(float x, float y) {}
