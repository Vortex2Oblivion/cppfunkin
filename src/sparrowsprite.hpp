#pragma once

#include "sprite.hpp"
#include "animation.hpp"

namespace funkin
{
    class SparrowSprite : public Sprite
    {
    private:
        std::map<std::string, funkin::Animation *> animations;

    public:
        SparrowSprite(double x, double y);
        ~SparrowSprite();
        void loadGraphic(std::string imagePath, std::string xmlPath);
        void addAnimationByPrefix(std::string name, std::string prefix, int framerate);

        void playAnimation(std::string name);

        void update(double delta);
        void draw();

        void centerOffsets();

        std::string xmlPath;
        funkin::Animation *currentAnimation;
        std::map<std::string, raylib::Vector2> offsets;
    };
}