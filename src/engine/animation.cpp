#include "animation.hpp"

#include <iostream>

engine::Animation::Animation(const std::vector<std::shared_ptr<engine::Frame>> &frames, const uint8_t framerate, const std::string &name) {
    this->frames = frames;
    this->framerate = framerate;
    this->currentFrame = 0;
    this->name = name;
}

engine::Animation::~Animation() {
    frames.clear();
}

void engine::Animation::update(const float delta) {
    if (framerate <= 0) {
        return;
    }

    frameTimer += delta;
    animationTimer += delta;

    while (frameTimer >= 1.0f / static_cast<float>(framerate)) {
        frameTimer -= 1.0f / static_cast<float>(framerate);
        if (currentFrame + 1 < frames.size()) {
            currentFrame++;
        }
    }
}

void engine::Animation::resetFrame() {
    currentFrame = 0;
    frameTimer = 0.0f;
    animationTimer = 0.0f;
}

bool engine::Animation::isFinished() const { return currentFrame + 1 >= frames.size(); }