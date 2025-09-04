#include "object.hpp"
#include "game.hpp"
#include <iostream>

funkin::Object::Object(float x, float y)
{
    this->position = raylib::Vector2(x, y);
    camera = funkin::Game::defaultCamera;
}
funkin::Object::~Object()
{
    alive = false;
}

void funkin::Object::update(float delta)
{
}

void funkin::Object::draw()
{
}