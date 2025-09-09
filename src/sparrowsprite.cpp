#include "sparrowsprite.hpp"

#include <pugixml.hpp>
#include <iostream>
#include <cstring>

funkin::SparrowSprite::SparrowSprite(float x, float y) : Sprite(x, y)
{
}

funkin::SparrowSprite::~SparrowSprite()
{
}

void funkin::SparrowSprite::loadGraphic(std::string imagePath, std::string xmlPath)
{
    funkin::Sprite::loadGraphic(imagePath);

    if (!raylib::FileExists(xmlPath))
    {
        std::cerr << "Could not find XML at path: " << xmlPath << "\n";
    }
    this->xmlPath = xmlPath;
}

void funkin::SparrowSprite::addAnimationByPrefix(std::string name, std::string prefix, int framerate)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xmlPath.c_str());

    std::vector<Frame *> foundFrames = {};
    for (auto frame : doc.child("TextureAtlas").children("SubTexture"))
    {
        const char *name = frame.attribute("name").as_string();
        if (strncmp(prefix.c_str(), name, strlen(prefix.c_str())) == 0) // find all animations that start with `prefix`
        {
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

            // foundFrames.push_back(new Frame(x, y, width, height, frameX, frameY, frameWidth, frameHeight));
            foundFrames.push_back(new Frame(rect, sourceSize, offset));

            // std::cout << "found frame: " << frame.attribute("name").as_string() << "\n";
        }
    }
    if (!foundFrames.empty())
    {
        animations[name] = new Animation(foundFrames, framerate);
        if (!offsets.count(name))
        {
            offsets[name] = raylib::Vector2(0, 0);
        }
    }
    else
    {
        std::cerr << "No frames found for animation: " << name << "\n";
    }
}

void funkin::SparrowSprite::playAnimation(std::string name)
{
    if (animations.count(name) == 0 || animations[name]->frames.empty())
    {
        std::cerr << "Animation not found or has no frames: " << name << "\n";
        return;
    }

    currentAnimation = animations[name];
    currentAnimation->resetFrame();
    if (offsets.count(name))
    {
        animationOffset = offsets[name];
    }
}

void funkin::SparrowSprite::update(float delta)
{
    funkin::Sprite::update(delta);
    if (currentAnimation != nullptr)
    {
        currentAnimation->update(delta);
    }
}

void funkin::SparrowSprite::centerOffsets()
{
    int frame = currentAnimation->currentFrame;

    offset.x = (dest.width - currentAnimation->frames[frame]->width) / 2;
    offset.y = (dest.height - currentAnimation->frames[frame]->height) / 2;
}

void funkin::SparrowSprite::draw()
{

    if (currentAnimation != nullptr && animations.size() > 0)
    {
        int frame = currentAnimation->currentFrame;

        source.x = currentAnimation->frames[frame]->x;
        source.y = currentAnimation->frames[frame]->y;
        source.width = currentAnimation->frames[frame]->width;
        source.height = currentAnimation->frames[frame]->height;

        dest.width = currentAnimation->frames[frame]->width * scale.x;
        dest.height = currentAnimation->frames[frame]->height * scale.y;
        dest.x = (dest.width / 2) + position.x + offset.x - animationOffset.x + currentAnimation->frames[frame]->frameX;
        dest.y = (dest.height / 2) + position.y + offset.y - animationOffset.y + currentAnimation->frames[frame]->frameY;

        origin = raylib::Vector2(dest.width / 2.0f, dest.height / 2.0f);

        if (isOnScreen())
        {
            texture->Draw(source, dest, origin, angle, color);
        }
    }
    else
    {
        funkin::Sprite::draw();
    }
}
raylib::Vector2 funkin::SparrowSprite::getMidpoint()
{
    return raylib::Vector2(position.x + (currentAnimation->frames[0]->frameWidth) - (1280 / 2), position.y + (currentAnimation->frames[0]->frameHeight) - 720);
}