#pragma once

#include "Vector2.hpp"
#include "animation.hpp"
#include "sprite.hpp"

namespace engine {
    class AnimatedSprite : public Sprite {
        public:
            AnimatedSprite(float x, float y);
            ~AnimatedSprite() override;

            void update(float delta) override;

            void addAnimation(const std::string &name, const std::vector<raylib::Rectangle> &rects, uint8_t framerate, bool looped = false);
            bool hasAnimation(const std::string &name) const;
            void playAnimation(const std::string &name);

            void updateHitbox();
            void centerOffsets();

            raylib::Vector2 getMidpoint() override;
            bool isOnScreen(float x, float y) override;

            void draw(float x, float y) override;

            std::unordered_map<std::string, std::shared_ptr<engine::Animation>> animations = {};
            std::shared_ptr<engine::Animation> currentAnimation = nullptr;
            std::map<std::string, raylib::Vector2> offsets = {};
            raylib::Vector2 animationOffset = raylib::Vector2::Zero();
            raylib::Vector2 offsetHitbox = raylib::Vector2::Zero();

        protected:
            raylib::Vector2 maxFrameSize = raylib::Vector2::Zero();
            raylib::Vector2 minFrameSize = raylib::Vector2(INFINITY, INFINITY);
    };
}  // namespace engine
