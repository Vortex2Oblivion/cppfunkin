#include "animatedsprite.hpp"

#include <iostream>

engine::AnimatedSprite::AnimatedSprite(float x, float y) : Sprite(x, y) {}

engine::AnimatedSprite::~AnimatedSprite() {
    offsets.clear();
    if (animations.empty()) {
        return;
    }

    while (animations.begin() != animations.end()) {
        std::map<std::string, Animation*>::iterator iter = animations.begin();
        if (iter->second != nullptr) {
            delete iter->second;
        }
        animations.erase(animations.begin());
    }
}

void engine::AnimatedSprite::update(float delta) {
    engine::Sprite::update(delta);
    if (currentAnimation != nullptr) {
        currentAnimation->update(delta);
    }
}

void engine::AnimatedSprite::addAnimation(std::string name, std::vector<raylib::Rectangle> rects, int framerate) {
    std::vector<Frame*> foundFrames = {};
    for (auto rect : rects) {
        foundFrames.push_back(new Frame(rect));
    }
    animations[name] = new Animation(foundFrames, framerate, name);
}

void engine::AnimatedSprite::playAnimation(std::string name) {
    if (animations.count(name) == 0 || animations[name]->frames.empty()) {
        std::cerr << "Animation not found or has no frames: " << name << "\n";
        return;
    }

    currentAnimation = animations[name];
    currentAnimation->resetFrame();
    if (offsets.count(name)) {
        animationOffset = offsets[name];
    }
}

void engine::AnimatedSprite::centerOffsets() {
    size_t frame = currentAnimation->currentFrame;

    offset.x = (dest.width - currentAnimation->frames[frame]->width) / 2;
    offset.y = (dest.height - currentAnimation->frames[frame]->height) / 2;
}

bool engine::AnimatedSprite::isOnScreen(float x, float y) {
    size_t frame = currentAnimation->currentFrame;
    raylib::Vector2 pos = camera->GetWorldToScreen(position + raylib::Vector2(x, y) + offset - animationOffset);
    return !((pos.y + (currentAnimation->frames[frame]->height * scale.y) < 0 || pos.y > raylib::Window::GetHeight()) ||
             (pos.x + (currentAnimation->frames[frame]->width * scale.x) < 0 || pos.x > raylib::Window::GetWidth()));
}

raylib::Vector2 engine::AnimatedSprite::getMidpoint() {
    auto animFrame = animations[animations.begin()->first]->frames[0];
    return raylib::Vector2(position.x + (animFrame->width / 2.0f), position.y + (animFrame->height / 2.0f));
}

void engine::AnimatedSprite::draw() { draw(0, 0); }

void engine::AnimatedSprite::draw(float x, float y) {
    if (currentAnimation != nullptr && animations.size() > 0) {
        size_t frame = currentAnimation->currentFrame;

        source.x = currentAnimation->frames[frame]->x;
        source.y = currentAnimation->frames[frame]->y;
        source.width = currentAnimation->frames[frame]->width;
        source.height = currentAnimation->frames[frame]->height;

        dest.width = currentAnimation->frames[frame]->width * scale.x;
        dest.height = currentAnimation->frames[frame]->height * scale.y;
        dest.x = (dest.width / 2) + position.x + offset.x - animationOffset.x + x;
        dest.y = (dest.height / 2) + position.y + offset.y - animationOffset.y + y;

        origin = raylib::Vector2(dest.width / 2.0f, dest.height / 2.0f);

        if (flipX) {
            source.width *= -1.0f;
        }

        if (isOnScreen()) {
            texture->Draw(source, dest, origin, angle, color);
        }
    } else {
        engine::Sprite::draw(x, y);
    }
}
