#pragma once

#include "animation.hpp"
#include "sprite.hpp"

namespace engine {
class AnimatedSprite : public Sprite {
   private:
    /* data */
   public:
    AnimatedSprite(float x, float y);
    ~AnimatedSprite();

    void update(float delta);

    void addAnimation(std::string name, std::vector<raylib::Rectangle> rects, int framerate);
    void playAnimation(std::string name);

    void centerOffsets();

    raylib::Vector2 getMidpoint();
    bool isOnScreen(float x = 0.0f, float y = 0.0f);

    void draw(float x = 0.0f, float y = 0.0f);

    std::map<std::string, engine::Animation*> animations = {};
    engine::Animation* currentAnimation;
    std::map<std::string, raylib::Vector2> offsets = {};
    raylib::Vector2 animationOffset;
};

}  // namespace engine
