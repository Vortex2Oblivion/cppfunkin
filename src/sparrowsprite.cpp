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

void funkin::SparrowSprite::addAnimationByPrefix(std::string name, std::string prefix, double framerate)
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
            foundFrames.push_back(new Frame(x, y, width, height));

            std::cout << "found frame: " << frame.attribute("name").as_string() << "\n";
        }
    }
    if (!foundFrames.empty())
    {
        animations[name] = new Animation(foundFrames);
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
    int frame = 0;

    source.x = animations[name]->frames[frame]->x;
    source.y = animations[name]->frames[frame]->y;
    source.width = animations[name]->frames[frame]->width;
    source.height = animations[name]->frames[frame]->height;
    dest.width = source.width * scale.x;
    dest.height = source.height * scale.y;
}

void funkin::SparrowSprite::update(double delta)
{
    funkin::Sprite::update(delta);
}

void funkin::SparrowSprite::draw()
{
    funkin::Sprite::draw();
}