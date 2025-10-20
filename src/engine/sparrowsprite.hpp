#pragma once

#include "animatedsprite.hpp"
#include "animation.hpp"
#include <pugixml.hpp>

namespace engine
{
    class SparrowSprite : public AnimatedSprite
    {
    private:
        pugi::xml_document doc;

    public:
        SparrowSprite(float x, float y);
        ~SparrowSprite();
        void loadGraphic(std::string imagePath, std::string xmlPath);
        void addAnimationByPrefix(std::string name, std::string prefix, int framerate);
        virtual void update(float delta);
        virtual void draw();
        virtual void draw(float x, float y);

        std::string xmlPath;
    };
}