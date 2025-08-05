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
        raylib::Vector2 position;
        bool alive = true;
    };
}