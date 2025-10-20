#include "object.hpp"
#include "game.hpp"
#include <cstdio>
#include <iostream>

engine::Object::Object()
{
    this->position = raylib::Vector2();
    camera = engine::Game::defaultCamera;
}

engine::Object::Object(float x, float y)
{
    this->position = raylib::Vector2(x, y);
    camera = engine::Game::defaultCamera;
}
engine::Object::~Object()
{
    alive = false;
}

void engine::Object::update(float delta)
{
}

void engine::Object::draw()
{
}

void engine::Object::draw(float x, float y)
{
}
