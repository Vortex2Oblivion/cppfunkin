#pragma once

#include <pugixml.hpp>

#include "Vector2.hpp"
#include "animatedsprite.hpp"
#include "animation.hpp"
#include "raylib.h"

namespace engine {
class SparrowSprite : public AnimatedSprite {
   private:
    pugi::xml_document doc;

   public:
    raylib::Vector2 originFactor = raylib::Vector2(0.5f, 0.5f);

    SparrowSprite(float x, float y);
    ~SparrowSprite() override;
    void loadGraphic(const std::string &imagePath, std::string xmlPath);
    void addAnimation(std::string name, const std::string &prefix, int framerate, std::vector<uint8_t> indices = {});
    void update(float delta) override;

    void draw(float x, float y) override;

    raylib::Vector2 getFrameSize(void) const;

    std::string xmlPath;
};
}  // namespace engine