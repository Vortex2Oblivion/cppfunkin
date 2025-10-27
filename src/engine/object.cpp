#include "object.hpp"

#include <cstdio>
#include <iostream>

#include "game.hpp"

engine::Object::Object(float x, float y) {
    this->position = raylib::Vector2(x, y);
    scrollFactor = raylib::Vector2::One();
    camera = engine::Game::defaultCamera;
}
engine::Object::~Object() { alive = false; }

void engine::Object::update(float delta) {}

void engine::Object::draw(float x, float y) {}
