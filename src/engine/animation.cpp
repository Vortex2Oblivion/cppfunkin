#include "animation.hpp"

#include <iostream>

engine::Animation::Animation(std::vector<engine::Frame*> frames, uint8_t framerate, std::string name) {
    this->frames = frames;
    this->framerate = framerate;
    this->currentFrame = 0;
    this->name = name;
}

engine::Animation::~Animation() {
    for (auto frame : frames) {
        if (frame == nullptr) {
            continue;
        }
        delete frame;
    }
    frames.clear();
}

void engine::Animation::update(float delta) {
    if (framerate <= 0) {
        return;
    }
    frameTimer += delta;
    animationTimer += delta;

    while (frameTimer >= 1.0f / framerate) {
        frameTimer -= 1.0f / framerate;
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

bool engine::Animation::isFinished() { return currentFrame + 1 >= frames.size(); }