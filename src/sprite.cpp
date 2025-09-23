#include "sprite.hpp"
#include <iostream>

std::map<std::string, raylib::Texture *> funkin::Sprite::texturePool;

funkin::Sprite::Sprite(float x, float y) : Object(x, y)
{
}

funkin::Sprite::~Sprite()
{
}

void funkin::Sprite::loadGraphic(std::string path)
{
    if (!texturePool.count(path))
    {
        if (!raylib::FileExists(path))
        {
            std::cerr << "Could not find image at path \"" << path << "\"\n";
        }
        else
        {
            texturePool[path] = new raylib::Texture(path);
        }
    }

    texture = texturePool[path];
    texture->SetFilter(TEXTURE_FILTER_BILINEAR);
    origin = raylib::Vector2(texture->width / 2.0f, texture->height / 2.0f);
    source = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    dest = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    angle = 0;
    color = WHITE;
}

void funkin::Sprite::update(float delta)
{
}

void funkin::Sprite::draw()
{
    funkin::Object::draw();

    dest.x = (texture->width / 2) + position.x * scale.x + offset.x;
    dest.y = (texture->height / 2) + position.y * scale.y + offset.y;
    dest.width = (float)(texture->width) * scale.x;
    dest.height = (float)(texture->height) * scale.y;
    if (isOnScreen())
    {
        texture->Draw(source, dest, origin, angle, color);
    }
}

bool funkin::Sprite::isOnScreen()
{
    return !((position.y + texture->height < 0 || position.y > GetScreenHeight()) || (position.x + texture->width < 0 || position.x > GetScreenWidth()));
}

raylib::Vector2 funkin::Sprite::getMidpoint()
{
    return raylib::Vector2(position.x + texture->width * 0.5f, position.y + texture->height * 0.5f);
}