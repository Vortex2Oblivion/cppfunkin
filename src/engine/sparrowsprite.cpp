#include "sparrowsprite.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <pugixml.hpp>

#include "animatedsprite.hpp"

engine::SparrowSprite::SparrowSprite(float x, float y) : AnimatedSprite(x, y) {}

engine::SparrowSprite::~SparrowSprite() {}

void engine::SparrowSprite::loadGraphic(std::string imagePath, std::string xmlPath) {
    engine::Sprite::loadGraphic(imagePath);

    this->xmlPath = xmlPath;
    if (!raylib::FileExists(xmlPath)) {
        std::cerr << "Could not find XML at path: " << xmlPath << "\n";
        return;
    }
    pugi::xml_parse_result result = doc.load_file(xmlPath.c_str());
}

void engine::SparrowSprite::addAnimation(std::string name, std::string prefix, int framerate, std::vector<uint8_t> indices) {
    std::vector<Frame*> foundFrames = {};
    uint8_t frameIndex = 0;
    for (auto frame : doc.child("TextureAtlas").children("SubTexture")) {
        const char* animationName = frame.attribute("name").as_string();

        if (strncmp(prefix.c_str(), animationName, strlen(prefix.c_str())) != 0)  // find all animations that start with `prefix`
        {
            continue;
        }

        bool addFrame = true;
        if (!indices.empty()) {
            addFrame = find(indices.begin(), indices.end(), frameIndex) != indices.end();
        }

        bool trimmed = frame.attribute("frameX");

        float x = frame.attribute("x").as_float();
        float y = frame.attribute("y").as_float();
        float width = frame.attribute("width").as_float();
        float height = frame.attribute("height").as_float();
        float frameX = frame.attribute("frameX").as_float();
        float frameY = frame.attribute("frameY").as_float();
        float frameWidth = frame.attribute("frameWidth").as_float();
        float frameHeight = frame.attribute("frameHeight").as_float();

        raylib::Rectangle rect = raylib::Rectangle(x, y, width, height);
        raylib::Vector2 offset = trimmed ? raylib::Vector2(-frameX, -frameY) : raylib::Vector2::Zero();
        raylib::Vector2 sourceSize = trimmed ? raylib::Vector2(frameWidth, frameHeight) : raylib::Vector2(width, height);

        if (addFrame) {
            foundFrames.push_back(new Frame(rect, sourceSize, offset));
        }
        frameIndex++;
    }
    if (foundFrames.empty()) {
        std::cerr << "No frames found for animation: " << name << "\n";
    }
    animations[name] = new Animation(foundFrames, framerate, name);
    if (!offsets.count(name)) {
        offsets[name] = raylib::Vector2(0, 0);
    }
}

void engine::SparrowSprite::update(float delta) { engine::AnimatedSprite::update(delta); }

void engine::SparrowSprite::draw(float x, float y) {
    if (currentAnimation == nullptr || animations.size() == 0) {
        engine::Sprite::draw(x, y);
        return;
    }
    size_t frame = currentAnimation->currentFrame;

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

    if (isOnScreen()) {
        texture->Draw(source, dest, origin * scale, angle, color);
    }
}
