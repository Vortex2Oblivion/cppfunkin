#pragma once

#include "animatedsprite.hpp"
#include "animation.hpp"

#include <raylib-cpp.hpp>
#include <pugixml.hpp>


namespace engine {
    class SparrowSprite : public AnimatedSprite {
       public:
        raylib::Vector2 originFactor = raylib::Vector2(0.5f, 0.5f);

        explicit SparrowSprite(float x = 0.0f, float y = 0.0f);
        ~SparrowSprite() override;
        void loadGraphic(const std::string &imagePath, const std::string &xmlPath);
        void addAnimation(const std::string &name, const std::string &prefix, uint8_t framerate, std::vector<uint8_t> indices = {}, bool looped = false);
        void update(float delta) override;

        void draw(float x, float y) override;

        raylib::Vector2 getFrameSize() const;

        std::string xmlPath;
       private:
        pugi::xml_document doc;
        pugi::xml_parse_result result;
    };
}  // namespace engine