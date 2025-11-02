#pragma once

#include "animation.hpp"
#include "sprite.hpp"

namespace engine {
class AnimatedSprite : public Sprite {
   private:
    /* data */
   public:
    AnimatedSprite(float x, float y);
    ~AnimatedSprite() override;

    void update(float delta) override;

    virtual void addAnimation(const std::string &name, const std::vector<raylib::Rectangle> &rects, int framerate);
    bool hasAnimation(const std::string &name);
    void playAnimation(const std::string &name);

    void centerOffsets();

    raylib::Vector2 getMidpoint() override;
    bool isOnScreen(float x, float y) override;

    void draw(float x, float y) override;

    std::map<std::string, engine::Animation*> animations = {};
    engine::Animation* currentAnimation = nullptr;
    std::map<std::string, raylib::Vector2> offsets = {};
    raylib::Vector2 animationOffset;
};

}  // namespace engine
