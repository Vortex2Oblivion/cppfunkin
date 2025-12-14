#include "sprite.hpp"

#include <iostream>

#include "game.hpp"

std::unordered_map<std::string, std::shared_ptr<raylib::Texture>> engine::Sprite::texturePool;

engine::Sprite::Sprite(const float x, const float y) : Object(x, y) {}

engine::Sprite::~Sprite() = default;

void engine::Sprite::loadGraphic(const std::string& path) {
    engine::Sprite::cacheTexture(path);

    texture = engine::Sprite::texturePool[path];
	if (texture != nullptr) {
		texture->SetFilter(TEXTURE_FILTER_BILINEAR);
		source = raylib::Rectangle(0, 0, static_cast<float>(texture->width), static_cast<float>(texture->height));
		dest = raylib::Rectangle(0, 0, static_cast<float>(texture->width), static_cast<float>(texture->height));
	}
    centerOrigin();
    angle = 0;
    color = WHITE;
}

void engine::Sprite::update(float delta) {}

void engine::Sprite::draw(const float x, const float y) {
    if (!visible || !texture) {
        return;
    }
    dest.x = (texture->GetSize().x / 2.0f) + position.x + offset.x + x;
    dest.y = (texture->GetSize().y / 2.0f) + position.y + offset.y + y;
    dest.width = static_cast<float>(texture->width) * scale.x;
    dest.height = static_cast<float>(texture->height) * scale.y;

    calculateScrollFactor();

    if (flipX) {
        source.width *= -1.0f;
    }

    if (isOnScreen(x, y)) {
        texture->Draw(source, dest, origin * scale, angle, color);
    }
}

bool engine::Sprite::isOnScreen(const float x, const float y) {
    const raylib::Vector2 pos = camera->GetWorldToScreen(position + offset - origin*scale + raylib::Vector2(x, y) + (dest.GetSize().Scale(0.5f)));
    return !((pos.y + (dest.GetHeight() * scale.y) < 0 || pos.y > raylib::Window::GetSize().y / camera->zoom) ||
             (pos.x + (dest.GetWidth() * scale.x) < 0 || pos.x > raylib::Window::GetSize().x / camera->zoom));
}

raylib::Vector2 engine::Sprite::getMidpoint() { return {position.x + texture->GetSize().x * 0.5f, position.y + texture->GetSize().y * 0.5f}; }

void engine::Sprite::screenCenter(const engine::Axes axes) {
    switch (axes) {
        case X:
            position.x = (raylib::Window::GetSize().x - dest.GetSize().x) / 2.0f;
            break;
        case Y:
            position.y = (raylib::Window::GetSize() - dest.GetSize()).y / 2.0f;
            break;
        default:
            screenCenter(engine::Axes::X);
            screenCenter(engine::Axes::Y);
    }
}

void engine::Sprite::centerOrigin() { origin = raylib::Vector2(dest.width / 2.0f, dest.height / 2.0f); }

void engine::Sprite::clearTextureCache() {
    texturePool.clear();
}

void engine::Sprite::cacheTexture(const std::string& path) {
    if (engine::Sprite::texturePool.contains(path)) {
        return;
    }
    if (!raylib::FileExists(path)) {
        std::cerr << "Could not find image at path \"" << path << "\"\n";
        return;
    }
    engine::Sprite::texturePool[path] = std::make_shared<raylib::Texture>(path);
}

void engine::Sprite::calculateScrollFactor() {
    dest.x += -camera->cameraPosition.x * (scrollFactor.x - 1.0f);
    dest.y += -camera->cameraPosition.y * (scrollFactor.y - 1.0f);
}

void engine::Sprite::add() {
    engine::Game::add(std::shared_ptr<engine::Sprite>(this));
}