#include "sprite.hpp"
#include <iostream>

map<string, raylib::Texture*> sprite::texturePool;

sprite::sprite(double x, double y) : object(x, y)
{
}

sprite::~sprite()
{
}

void sprite::loadGraphic(string path)
{
    if (!texturePool.count(path))
    {
        texturePool[path] = new raylib::Texture(path);
    }

    texture = texturePool[path];
    origin = raylib::Vector2(texture->width / 2, texture->height / 2);
    source = raylib::Rectangle(0, 0, texture->width, texture->height);
    dest = raylib::Rectangle(0, 0, texture->width, texture->height);
    angle = 0;
    color = WHITE;
}

void sprite::update(double delta)
{
    draw();
}

void sprite::draw()
{
    dest.x = (texture->width / 2) + position.x;
    dest.y = (texture->height / 2) + position.y;
    if(isOnScreen()){
        texture->Draw(source, dest, origin, angle, color);
    }
}

bool sprite::isOnScreen()
{
    return !((position.y + texture->height < 0 || position.y > GetScreenHeight()) || (position.x + texture->width < 0 || position.x > GetScreenWidth()));
}