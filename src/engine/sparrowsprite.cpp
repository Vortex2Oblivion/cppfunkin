#include "sparrowsprite.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

#include "animatedsprite.hpp"
#include "raylib.h"

engine::SparrowSprite::SparrowSprite(const float x, const float y) : AnimatedSprite(x, y) {}

engine::SparrowSprite::~SparrowSprite() = default;

void engine::SparrowSprite::loadGraphic(const std::string &imagePath, const std::string& xmlPath) {
    engine::Sprite::loadGraphic(imagePath);

    this->xmlPath = xmlPath;
    if (!raylib::FileExists(xmlPath)) {
        std::cerr << "Could not find XML at path: " << xmlPath << "\n";
        return;
    }
    result = doc.load_file(xmlPath.c_str());
}

void engine::SparrowSprite::addAnimation(const std::string &name, const std::string &prefix, const uint8_t framerate, std::vector<uint8_t> indices, bool looped) {
    std::vector<std::shared_ptr<engine::Frame>> foundFrames = {};
    uint8_t frameIndex = 0;
    for (auto frame : doc.child("TextureAtlas").children("SubTexture")) {
        const auto animationName = frame.attribute("name").as_string();

        if (strncmp(prefix.c_str(), animationName, strlen(prefix.c_str())) != 0) { // find all animations that start with `prefix`
            continue;
        }

        bool addFrame = true;

        if (!indices.empty()) {
            addFrame = std::ranges::find(indices, frameIndex) != indices.end();
        }

        const bool trimmed = frame.attribute("frameX");

        const float x = frame.attribute("x").as_float();
        const float y = frame.attribute("y").as_float();
        const float width = frame.attribute("width").as_float();
        const float height = frame.attribute("height").as_float();
        const float frameX = frame.attribute("frameX").as_float();
        const float frameY = frame.attribute("frameY").as_float();
        const float frameWidth = frame.attribute("frameWidth").as_float();
        const float frameHeight = frame.attribute("frameHeight").as_float();

        const auto rect = raylib::Rectangle(x, y, width, height);
        const raylib::Vector2 offset = trimmed ? raylib::Vector2(-frameX, -frameY) : raylib::Vector2::Zero();
        const raylib::Vector2 sourceSize = trimmed ? raylib::Vector2(frameWidth, frameHeight) : raylib::Vector2(width, height);

        if (addFrame) {
            foundFrames.push_back(std::make_shared<engine::Frame>(rect, sourceSize, offset));

            maxFrameSize.x = std::max(maxFrameSize.x, rect.width);
            maxFrameSize.y = std::max(maxFrameSize.y, rect.height);

            minFrameSize.x = std::min(minFrameSize.x, rect.width);
            minFrameSize.y = std::min(minFrameSize.y, rect.height);
        }

        frameIndex++;
    }

    if (foundFrames.empty()) {
        std::cerr << "No frames found for animation: " << name << "\n";
    }

    animations[name] = std::make_shared<engine::Animation>(foundFrames, framerate, name, looped);
    if (!offsets.contains(name)) {
        offsets[name] = raylib::Vector2(0, 0);
    }
}

void engine::SparrowSprite::update(const float delta) { engine::AnimatedSprite::update(delta); }


void engine::SparrowSprite::draw(const float x, const float y) {
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
    dest.x = (dest.width / 2) + position.x + offset.x - animationOffset.x + currentAnimation->frames[frame]->frameX + x;
    dest.y = (dest.height / 2) + position.y + offset.y - animationOffset.y + currentAnimation->frames[frame]->frameY + y;

    calculateScrollFactor();

    origin = raylib::Vector2(dest.width * originFactor.x, dest.height * originFactor.y);

    if (flipX) {
        source.width *= -1.0f;
    }

    if (isOnScreen(x, y)) {
        texture->Draw(source, dest, origin * scale, angle, color);
    }
}

raylib::Vector2 engine::SparrowSprite::getFrameSize() const {
    if (currentAnimation == nullptr || animations.empty()) {
        return raylib::Vector2::Zero();
    }

    const size_t frame = currentAnimation->currentFrame;
    return {currentAnimation->frames[frame]->width, currentAnimation->frames[frame]->height};
}
