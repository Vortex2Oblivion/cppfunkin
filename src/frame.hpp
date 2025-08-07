#pragma once

#include <raylib-cpp.hpp>

namespace funkin
{
    class Frame
    {
    private:
        /* data */
    public:
        Frame(raylib::Rectangle rect);
        Frame(float x, float y, float width, float height);
        ~Frame();

        float x;
        float y;
        float width;
        float height;
    };
}