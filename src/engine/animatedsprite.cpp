#include "animatedsprite.hpp"
#include "Vector2.hpp"
#include "raylib.h"

#include <iostream>

engine::AnimatedSprite::AnimatedSprite(const float x, const float y) : Sprite(x, y) {}

engine::AnimatedSprite::~AnimatedSprite() {
    offsets.clear();
    animations.clear();
}

void engine::AnimatedSprite::update(const float delta) {
    engine::Sprite::update(delta);
    if (currentAnimation != nullptr) {
        currentAnimation->update(delta);
    }
}

void engine::AnimatedSprite::addAnimation(const std::string& name, const std::vector<raylib::Rectangle>& rects, const int framerate) {
    std::vector<std::shared_ptr<engine::Frame>> foundFrames = {};
    for (const auto rect : rects) {
        foundFrames.push_back(std::make_shared<engine::Frame>(rect));
    }
    animations[name] = std::make_shared<engine::Animation>(foundFrames, framerate, name);
}

bool engine::AnimatedSprite::hasAnimation(const std::string& name) const { return animations.contains(name); }

void engine::AnimatedSprite::playAnimation(const std::string& name) {
    if (!animations.contains(name) || animations[name]->frames.empty()) {
        std::cerr << "Animation not found or has no frames: " << name << "\n";
        return;
    }

    currentAnimation = animations[name];
    currentAnimation->resetFrame();
    if (offsets.contains(name)) {
        animationOffset = offsets[name];
    }
}

void engine::AnimatedSprite::centerOffsets() {
    const size_t frame = currentAnimation->currentFrame;

    offset.x = (dest.width - currentAnimation->frames[frame]->width) / 2;
    offset.y = (dest.height - currentAnimation->frames[frame]->height) / 2;
}

bool engine::AnimatedSprite::isOnScreen(const float x, const float y) {
    const raylib::Vector2 pos = camera->GetWorldToScreen(dest.GetSize().Scale(0.5f) + dest.GetPosition() + offset - animationOffset - raylib::Vector2(x, y) - (origin * scale));
    return !((pos.y + (dest.height * scale.y) < 0 || pos.y - (dest.height * scale.y)> static_cast<float>(raylib::Window::GetHeight()) / camera->zoom) ||
             (pos.x + (dest.width * scale.x) < 0 || pos.x - (dest.width * scale.x) > static_cast<float>(raylib::Window::GetWidth()) / camera->zoom));
}

raylib::Vector2 engine::AnimatedSprite::getMidpoint() {
    const auto animFrame = animations[animations.begin()->first]->frames[0];
    auto returnPos = raylib::Vector2(position.x + (animFrame->width / 2.0f), position.y + (animFrame->height / 2.0f));
    returnPos -= raylib::Vector2(1280.0f / 2.0f, 720.0f / 2.0f);
    return returnPos;
}

void engine::AnimatedSprite::draw(const float x, const float y) {
    if (currentAnimation == nullptr || animations.empty()) {
        engine::Sprite::draw(x, y);
        return;
    }
    const size_t frame = currentAnimation->currentFrame;

    source.x = currentAnimation->frames[frame]->x;
    source.y = currentAnimation->frames[frame]->y;
    source.width = currentAnimation->frames[frame]->width;
    source.height = currentAnimation->frames[frame]->height;

    dest.width = currentAnimation->frames[frame]->width * scale.x;
    dest.height = currentAnimation->frames[frame]->height * scale.y;
    dest.x = (dest.width / 2) + position.x + offset.x - animationOffset.x + x;
    dest.y = (dest.height / 2) + position.y + offset.y - animationOffset.y + y;

    calculateScrollFactor();

    if (flipX) {
        source.width *= -1.0f;
    }

    if (isOnScreen(x, y)) {
        texture->Draw(source, dest, origin * scale, angle, color);
    }
}
