#include "sparrowsprite.hpp"

#include <pugixml.hpp>
#include <iostream>
#include <cstring>

funkin::SparrowSprite::SparrowSprite(double x, double y) : Sprite(x, y)
{
}

funkin::SparrowSprite::~SparrowSprite()
{
}

void funkin::SparrowSprite::loadGraphic(std::string imagePath, std::string xmlPath)
{
    funkin::Sprite::loadGraphic(imagePath);

    this->xmlPath = xmlPath;
}

void funkin::SparrowSprite::addAnimationByPrefix(std::string name, std::string prefix, int framerate)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xmlPath.c_str());

    std::vector<Frame *> foundFrames = {};
    for (auto frame : doc.child("TextureAtlas").children("SubTexture"))
    {
        if (strncmp(prefix.c_str(), frame.attribute("name").as_string(), strlen(prefix.c_str())) == 0)
        {
            float x = frame.attribute("x").as_float();
            float y = frame.attribute("y").as_float();
            float width = frame.attribute("width").as_float();
            float height = frame.attribute("height").as_float();
            float frameX = frame.attribute("frameX").as_float();
            float frameY = frame.attribute("frameY").as_float();
            float frameWidth = frame.attribute("frameWidth").as_float();
            float frameHeight = frame.attribute("frameHeight").as_float();
            foundFrames.push_back(new Frame(x, y, width, height, frameX, frameY, frameWidth, frameHeight));

            // std::cout << "found frame: " << frame.attribute("name").as_string() << "\n";
        }
    }
    if (!foundFrames.empty())
    {
        animations[name] = new Animation(foundFrames, framerate);
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
    currentAnimation->currentFrame = 0;
}

void funkin::SparrowSprite::update(double delta)
{
    funkin::Sprite::update(delta);
    if (currentAnimation != nullptr)
    {
        currentAnimation->update(delta);

        int frame = currentAnimation->currentFrame;

        source.x = currentAnimation->frames[frame]->x;
        source.y = currentAnimation->frames[frame]->y;
        source.width = currentAnimation->frames[frame]->width;
        source.height = currentAnimation->frames[frame]->height;
        dest.width = currentAnimation->frames[frame]->frameWidth * scale.x;
        dest.height = currentAnimation->frames[frame]->frameHeight * scale.y;
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
    funkin::Sprite::draw();
}