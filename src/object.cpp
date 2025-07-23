#include "object.hpp"

object::object(double x, double y)
{
    this->position = raylib::Vector2(x, y);
}

object::~object()
{
    alive = false;
}

void object::update(double delta)
{
}