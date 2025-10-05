#pragma once

#include <raylib-cpp.hpp>

namespace engine
{
    class Object
    {
    private:
        /* data */
    public:
        Object();
        Object(float x, float y);
        virtual ~Object();
        virtual void update(float delta);
        virtual void draw();
        raylib::Vector2 position;
        bool alive = true;
        raylib::Camera2D *camera;
    };
}