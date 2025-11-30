#include "healthicon.hpp"

funkin::HealthIcon::HealthIcon(const std::string& character, float x, float y) : engine::AnimatedSprite(x, y) {
    std::string iconPath = "assets/characters/" + character + "/icon.png";
    
    if (!raylib::FileExists(iconPath)) {
        iconPath = "assets/images/face.png";
    }

    loadGraphic(iconPath);
    addAnimation("default", {raylib::Rectangle(0.0f, 0.0f, texture->width / 2.0f, static_cast<float>(texture->height))}, 0);
    addAnimation("losing", {raylib::Rectangle(texture->width / 2.0f, 0.0f, texture->width / 2.0f,  static_cast<float>(texture->height))}, 0);
    playAnimation("default");
}

funkin::HealthIcon::~HealthIcon() = default;