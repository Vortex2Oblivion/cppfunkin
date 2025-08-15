#pragma once

#include <raylib-cpp.hpp>

namespace funkin
{
    class Object
    {
    private:
        /* data */
    public:
        Object(double x, double y);
        virtual ~Object();
        virtual void update(double delta);
        virtual void draw();
        raylib::Vector2 position;
        bool alive = true;
        raylib::Camera2D *camera;
    };
}