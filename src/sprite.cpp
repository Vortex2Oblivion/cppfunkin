#include "sprite.hpp"
#include <iostream>

std::map<std::string, raylib::Texture *> funkin::Sprite::texturePool;

funkin::Sprite::Sprite(double x, double y) : Object(x, y)
{
}

funkin::Sprite::~Sprite()
{
}

void funkin::Sprite::loadGraphic(std::string path)
{
    if (!texturePool.count(path))
    {
        texturePool[path] = new raylib::Texture(path);
    }

    texture = texturePool[path];
    texture->SetFilter(TEXTURE_FILTER_BILINEAR);
    origin = raylib::Vector2(texture->width / 2.0f, texture->height / 2.0f);
    source = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    dest = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    angle = 0;
    color = WHITE;
}

void funkin::Sprite::update(double delta)
{
    draw();
}

void funkin::Sprite::draw()
{
    dest.x = (texture->width / 2) + position.x;
    dest.y = (texture->height / 2) + position.y;
    if (isOnScreen())
    {
        texture->Draw(source, dest, origin, angle, color);
    }
}

bool funkin::Sprite::isOnScreen()
{
    return !((position.y + texture->height < 0 || position.y > GetScreenHeight()) || (position.x + texture->width < 0 || position.x > GetScreenWidth()));
}