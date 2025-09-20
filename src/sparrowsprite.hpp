#pragma once

#include "sprite.hpp"
#include "animation.hpp"
#include <pugixml.hpp>


namespace funkin
{
    class SparrowSprite : public Sprite
    {
    private:
        std::map<std::string, funkin::Animation *> animations;
        pugi::xml_document doc;

    public:
        SparrowSprite(float x, float y);
        ~SparrowSprite();
        void loadGraphic(std::string imagePath, std::string xmlPath);
        void addAnimationByPrefix(std::string name, std::string prefix, int framerate);

        void playAnimation(std::string name);

        void update(float delta);
        void draw();

        raylib::Vector2 getMidpoint();

        void centerOffsets();

        std::string xmlPath;
        funkin::Animation *currentAnimation;
        std::map<std::string, raylib::Vector2> offsets;
        raylib::Vector2 animationOffset;
    };
}