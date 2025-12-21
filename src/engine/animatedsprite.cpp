#include "animatedsprite.hpp"

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

void engine::AnimatedSprite::addAnimation(const std::string& name, const std::vector<raylib::Rectangle>& rects, const uint8_t framerate, bool looped) {
    std::vector<std::shared_ptr<engine::Frame>> foundFrames = {};
    for (const auto rect : rects) {
        foundFrames.push_back(std::make_shared<engine::Frame>(rect));
    }
	animations[name] = std::make_shared<engine::Animation>(foundFrames, framerate, name, looped);
	if (firstFrame == nullptr) {
		firstFrame = animations[animations.begin()->first]->frames[0];
	}
}

bool engine::AnimatedSprite::hasAnimation(const std::string& name) const { return animations.contains(name); }

void engine::AnimatedSprite::playAnimation(const std::string& name) {
    if (!animations.contains(name) || animations[name]->frames.empty()) {
        std::cerr << "Animation not found or has no frames: " << name << "\n";
        return;
    }

    const bool setFirstHitbox = currentAnimation == nullptr;

    currentAnimation = animations[name];
    currentAnimation->resetFrame();
    if (offsets.contains(name)) {
        animationOffset = offsets[name];
    }

    if (setFirstHitbox) {
        updateHitbox();
    }
}

void engine::AnimatedSprite::updateHitbox() {
    if (currentAnimation != nullptr) {
        const size_t frame = currentAnimation->currentFrame;
        offsetHitbox.x = currentAnimation->frames[frame]->frameWidth;
        offsetHitbox.y = currentAnimation->frames[frame]->frameHeight;
    }
}

void engine::AnimatedSprite::centerOffsets() {
    if (currentAnimation != nullptr) {
        const size_t frame = currentAnimation->currentFrame;
        const auto currentFrame = currentAnimation->frames[frame];
        offset.x = (offsetHitbox.x - currentFrame->width) * 0.5f + (currentFrame->width - currentFrame->frameWidth + currentFrame->frameX * 0.5f) * 0.5f;
        offset.y = (offsetHitbox.y - currentFrame->height) * 0.5f + (currentFrame->height - currentFrame->frameHeight + currentFrame->frameY * 0.5f) * 0.5f;
    }
}

bool engine::AnimatedSprite::isOnScreen(const float x, const float y) {
    const raylib::Vector2 pos = camera->GetWorldToScreen(dest.GetSize().Scale(0.5f) + dest.GetPosition() + offset - animationOffset - raylib::Vector2(x, y) - (origin * scale));
    return !((pos.y + (dest.height * scale.y) < 0 || pos.y - (dest.height * scale.y)> static_cast<float>(raylib::Window::GetHeight()) / camera->zoom) ||
             (pos.x + (dest.width * scale.x) < 0 || pos.x - (dest.width * scale.x) > static_cast<float>(raylib::Window::GetWidth()) / camera->zoom));
}

raylib::Vector2 engine::AnimatedSprite::getMidpoint() {
    auto returnPos = raylib::Vector2(position.x + (offsetHitbox.x / 2.0f), position.y + (offsetHitbox.y / 2.0f));
    returnPos -= raylib::Vector2(1280.0f / 2.0f, 720.0f / 2.0f);
    return returnPos;
}

void engine::AnimatedSprite::draw(const float x, const float y) {
    if (!visible || currentAnimation == nullptr || animations.empty()) {
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

void engine::AnimatedSprite::screenCenter(const engine::Axes axes) {
    switch (axes) {
        case X:
            position.x = (raylib::Window::GetSize() - offsetHitbox).x / 2.0f;
            break;
        case Y:
            position.y = (raylib::Window::GetSize() - offsetHitbox).y / 2.0f;
            break;
        default:
            screenCenter(engine::Axes::X);
            screenCenter(engine::Axes::Y);
    }
}

