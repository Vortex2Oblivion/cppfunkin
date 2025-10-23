#include "healthicon.hpp"

funkin::HealthIcon::HealthIcon(std::string character, float x, float y) : engine::AnimatedSprite(x, y) {
    std::string iconPath = "assets/characters/" + character + "/icon.png";
    if (!FileExists(iconPath.c_str())) {
        iconPath = "assets/images/face.png";
    }
    loadGraphic(iconPath);
    addAnimation("default", {raylib::Rectangle(0, 0, texture->width / 2.0f, texture->height)}, 0);
    addAnimation("losing", {raylib::Rectangle(texture->width / 2.0f, 0, texture->width / 2.0f, texture->height)}, 0);
    playAnimation("default");
}

funkin::HealthIcon::~HealthIcon() {}