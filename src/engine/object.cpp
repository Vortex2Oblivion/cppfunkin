#include "object.hpp"

#include <cstdio>
#include <iostream>

#include "game.hpp"

engine::Object::Object(const float x, const float y) {
    this->position = raylib::Vector2(x, y);
    scrollFactor = raylib::Vector2::One();
    camera = engine::Game::defaultCamera;
}
engine::Object::~Object() {
    printf("Object::~Object\n");
    alive = false;
}

void engine::Object::update(const float delta) {}

void engine::Object::draw(float x, float y) {}
