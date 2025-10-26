#include "sprite.hpp"

#include <iostream>

#include "Vector2.hpp"

std::map<std::string, raylib::Texture*> engine::Sprite::texturePool;

engine::Sprite::Sprite(float x, float y) : Object(x, y) {}

engine::Sprite::~Sprite() {}

void engine::Sprite::loadGraphic(std::string path) {
    engine::Sprite::cacheTexture(path);

    texture = engine::Sprite::texturePool[path];
    texture->SetFilter(TEXTURE_FILTER_BILINEAR);
    source = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    dest = raylib::Rectangle(0, 0, (float)(texture->width), (float)(texture->height));
    centerOrigin();
    angle = 0;
    color = WHITE;
}

void engine::Sprite::update(float delta) {}

void engine::Sprite::draw(float x, float y) {
    if (!texture) {
        return;
    }
    dest.x = (texture->width / 2.0f) + position.x + offset.x + x;
    dest.y = (texture->height / 2.0f) + position.y + offset.y + y;
    dest.width = (float)(texture->width) * scale.x;
    dest.height = (float)(texture->height) * scale.y;

    if (flipX) {
        source.width *= -1.0f;
    }

    if (isOnScreen(x, y)) {
        texture->Draw(source, dest, origin * scale, angle, color);
    }
}

bool engine::Sprite::isOnScreen(float x, float y) {
    raylib::Vector2 pos = camera->GetWorldToScreen(position + offset - origin + raylib::Vector2(x, y) + (texture->GetSize().Scale(0.5f)));
    return !((pos.y + (texture->height * scale.y) < 0 || pos.y > raylib::Window::GetHeight()) ||
             (pos.x + (texture->width * scale.x) < 0 || pos.x > raylib::Window::GetWidth()));
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

void engine::Sprite::centerOrigin() {
    origin = raylib::Vector2(dest.width / 2.0f, dest.height / 2.0f);
}

void engine::Sprite::clearTextureCache() {
    for (std::pair<std::string, raylib::Texture*> pair : engine::Sprite::texturePool) {
        delete pair.second;
    }
    texturePool.clear();
}

void engine::Sprite::cacheTexture(std::string path) {
    if (engine::Sprite::texturePool.count(path)) {
        return;
    }
    if (!raylib::FileExists(path)) {
        std::cerr << "Could not find image at path \"" << path << "\"\n";
        return;
    }
    engine::Sprite::texturePool[path] = new raylib::Texture(path);
}