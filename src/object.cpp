#include "object.hpp"

funkin::Object::Object(double x, double y)
{
    this->position = raylib::Vector2(x, y);
}

funkin::Object::~Object()
{
    alive = false;
}

void funkin::Object::update(double delta)
{
}