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
        Frame(int x, int y, int width, int height);
        ~Frame();

        int x;
        int y;
        int width;
        int height;
    };
}