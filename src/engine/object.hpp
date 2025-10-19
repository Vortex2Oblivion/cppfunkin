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
        virtual void draw(float x, float y);
        raylib::Vector2 position;
        raylib::Camera2D *camera;
        bool alive = true;
    };
}