#pragma once

#include <raylib-cpp.hpp>

namespace funkin
{
    class Frame
    {
    private:
        /* data */
    public:
        Frame(float x, float y, float width, float height, float frameX, float frameY, float frameWidth, float frameHeight);
        ~Frame();

        float x;
        float y;
        float width;
        float height;
        float frameX;
        float frameY;
        float frameWidth;
        float frameHeight;
    };
}