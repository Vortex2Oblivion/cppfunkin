#include "sprite.hpp"

#include <iostream>

std::map<std::string, raylib::Texture*> engine::Sprite::texturePool;

engine::Sprite::Sprite(float x, float y) : Object(x, y) {}

engine::Sprite::~Sprite() {}

void engine::Sprite::loadGraphic(std::string path) {
    if (!engine::Sprite::texturePool.count(path)) {
        if (!raylib::FileExists(path)) {
            std::cerr << "Could not find image at path \"" << path << "\"\n";
        } else {
            engine::Sprite::texturePool[path] = new raylib::Texture(path);
        }
    }

    texture = engine::Sprite::texturePool[path];
    texture->SetFilter(TEXTURE_FILTER_BILINEAR);
    origin = raylib::Vector2(texture->width / 2.0f, texture->height / 2.0f);
    source = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    dest = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    angle = 0;
    color = WHITE;
}

void engine::Sprite::update(float delta) {}

void engine::Sprite::draw() { draw(0, 0); }

void engine::Sprite::draw(float x, float y) {
    dest.x = (texture->width / 2.0f) + position.x * scale.x + offset.x + x;
    dest.y = (texture->height / 2.0f) + position.y * scale.y + offset.y + y;
    dest.width = (float)(texture->width) * scale.x;
    dest.height = (float)(texture->height) * scale.y;
    if (isOnScreen()) {
        texture->Draw(source, dest, origin, angle, color);
    }
}

bool engine::Sprite::isOnScreen() {
    raylib::Vector2 pos = camera->GetWorldToScreen(position);
    return !((pos.y + texture->height < 0 || pos.y > raylib::Window::GetHeight()) ||
             (pos.x + texture->width < 0 || pos.x > raylib::Window::GetWidth()));
}

raylib::Vector2 engine::Sprite::getMidpoint() { return raylib::Vector2(position.x + texture->width * 0.5f, position.y + texture->height * 0.5f); }

void engine::Sprite::screenCenter() {
    position.x = (raylib::Window::GetWidth() - texture->width) / 2.0f;
    position.y = (raylib::Window::GetHeight() - texture->height) / 2.0f;
}
void engine::Sprite::screenCenter(engine::Axes axes) {
    switch (axes) {
        case X:
            position.x = (raylib::Window::GetWidth() - texture->width) / 2.0f;
            break;
        case Y:
            position.y = (raylib::Window::GetHeight() - texture->height) / 2.0f;
            break;
        default:
            screenCenter();
    }
}

void engine::Sprite::clearTextureCache() {
    for (std::pair<std::string, raylib::Texture*> pair : engine::Sprite::texturePool) {
        delete pair.second;
    }
    texturePool.clear();
}
