#include "healthbar.hpp"

funkin::HealthBar::HealthBar(float x, float y, std::string iconLeft, std::string iconRight, raylib::Color colorLeft, raylib::Color colorRight)
    : engine::Group<engine::Object>(x, y) {
    bar = new engine::Bar(x, y, 601.0f - 8.0f, 19.0f - 8.0f, colorLeft, colorRight, 8);
    bar->fillDirection = engine::FillDirection::RIGHT_TO_LEFT;
    add(bar);
    iconP1 = new funkin::HealthIcon(iconRight, 0.0f, 0.0f);
    iconP1->flipX = true;
    iconP1->origin = raylib::Vector2(0.0f, 0.0f);
    add(iconP1);
    iconP2 = new funkin::HealthIcon(iconLeft, 0.0f, 0.0f);
    iconP2->origin = raylib::Vector2(300.0f, 0.0f);
    add(iconP2);
}

funkin::HealthBar::~HealthBar() {}

void funkin::HealthBar::update(float delta) {
    engine::Group<engine::Object>::update(delta);
    iconP2->position.x = bar->position.x + bar->getIntersection() + 150.0f - 26.0f * 2.0f;
    iconP2->position.y = bar->position.y - (300.0f - 19.0f) / 2.0f;

    iconP1->position.x = bar->position.x + bar->getIntersection() - 150.0f + 26.0f * 2.0f + 13.0f;
    iconP1->position.y = bar->position.y - (300.0f - 19.0f) / 2.0f;

    iconP1->playAnimation("default");
    iconP2->playAnimation("default");

    if (bar->percent >= 80) {
        iconP2->playAnimation("losing");
    } else if (bar->percent <= 20) {
        iconP1->playAnimation("losing");
    }

    float multP1 = Lerp(1.0f, iconP1->scale.x, expf(-delta * 9.0f));
    iconP1->scale = raylib::Vector2(multP1, multP1);

    float multP2 = Lerp(1.0f, iconP2->scale.x, expf(-delta * 9.0f));
    iconP2->scale = raylib::Vector2(multP2, multP2);
}

void funkin::HealthBar::bopIcons(float scaleFactor) {
    iconP1->scale = raylib::Vector2(scaleFactor, scaleFactor);
    iconP2->scale = raylib::Vector2(scaleFactor, scaleFactor);
}
