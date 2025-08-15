#include "object.hpp"
#include "game.hpp"

funkin::Object::Object(double x, double y)
{
    this->position = raylib::Vector2(x, y);
    camera = funkin::Game::defaultCamera;
}
funkin::Object::~Object()
{
    alive = false;
}

void funkin::Object::update(double delta)
{
}