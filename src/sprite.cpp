#include "sprite.hpp"
#include <iostream>

sprite::sprite(double x, double y) : object(x, y)
{
}

sprite::~sprite() {
    
}

void sprite::loadGraphic(string path)
{
    texture = raylib::Texture(path);
    origin = raylib::Vector2(texture.width / 2, texture.height / 2);
    source = raylib::Rectangle(0, 0, texture.width, texture.height);
    dest = raylib::Rectangle(0, 0, texture.width, texture.height);
    angle = 0;
    color = WHITE;
}


void sprite::update(double delta)
{
    draw();
}

void sprite::draw()
{
    dest.x = (texture.width / 2) + position.x;
    dest.y = (texture.height / 2) + position.y;
    texture.Draw(source, dest, origin, angle, color);
}

bool sprite::isOnScreen()
{
    return !((position.y + texture.height < 0 || position.y > GetScreenHeight()) || (position.x + texture.width < 0 || position.x > GetScreenWidth()));
}