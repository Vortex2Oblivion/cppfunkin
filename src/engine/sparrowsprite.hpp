#pragma once

#include <pugixml.hpp>

#include "Vector2.hpp"
#include "animatedsprite.hpp"
#include "animation.hpp"

namespace engine {
class SparrowSprite : public AnimatedSprite {
   private:
    pugi::xml_document doc;

   public:
    raylib::Vector2 originFactor = raylib::Vector2(0.5f, 0.5f);

    SparrowSprite(float x, float y);
    ~SparrowSprite();
    void loadGraphic(std::string imagePath, std::string xmlPath);
    void addAnimation(std::string name, std::string prefix, int framerate, std::vector<uint8_t> indices = {});
    virtual void update(float delta);
    virtual void draw(float x = 0.0f, float y = 0.0f);

    std::string xmlPath;
};
}  // namespace engine