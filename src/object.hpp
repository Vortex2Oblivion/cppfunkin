#pragma once

#include <raylib-cpp.hpp>

class object
{
private:
    /* data */
public:
    object(double x, double y);
    ~object();
    virtual void update(double delta);
    raylib::Vector2 position;
};