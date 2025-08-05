#pragma once

#include "sprite.hpp"

namespace funkin
{
    class SparrowSprite : public Sprite
    {
    private:
        void draw();
    public:
        SparrowSprite(double x, double y);
        ~SparrowSprite();
        void loadGraphic(std::string imagePath, std::string xmlPath);
    };
}