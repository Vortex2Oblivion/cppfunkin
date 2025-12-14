#include "bar.hpp"

#include "axes.hpp"

engine::Bar::Bar(float x, float y, float width, float height,
                 const raylib::Color colorLeft, const raylib::Color colorRight,
                 const float outlineSize, const raylib::Color colorOutline)
    : Sprite(x, y) {
    rectBottom = std::make_unique<raylib::Rectangle>(x, y, width, height);
    rectTop = std::make_unique<raylib::Rectangle>(x, y, width * (percent / 100.0f), height);
    rectOutline = std::make_unique<raylib::Rectangle>(x - outlineSize / 2.0f, y - outlineSize / 2.0f, width + outlineSize, height + outlineSize);
    this->colorLeft = colorLeft;
    this->colorRight = colorRight;
    this->colorOutline = colorOutline;
    this->outlineSize = outlineSize;
    this->origin = raylib::Vector2(rectOutline->width / 2, rectOutline->height / 2);
}

engine::Bar::~Bar() = default;


void engine::Bar::screenCenter(const engine::Axes axes) {
    switch (axes) {
        case X:
            position.x = (raylib::Window::GetSize().x - rectOutline->width) / 2;
            break;
        case Y:
            position.y = (raylib::Window::GetSize().y - rectOutline->height) / 2;
            break;
        default:
            screenCenter(engine::Axes::X);
            screenCenter(engine::Axes::Y);
    }
}

void engine::Bar::update(float delta) {
    rectTop->x = rectBottom->x = position.x;
    rectTop->y = rectBottom->y = position.y;

    rectOutline->width = rectBottom->x - outlineSize / 2.0f;
    rectOutline->height = rectBottom->y - outlineSize / 2.0f;
    rectOutline->width = rectBottom->width + outlineSize;
    rectOutline->height = rectBottom->height + outlineSize;
    rectOutline->x = rectBottom->x - outlineSize / 2.0f;
    rectOutline->y = rectBottom->y - outlineSize / 2.0f;

    switch (fillDirection) {
        case LEFT_TO_RIGHT:
            rectTop->width = Clamp(rectBottom->width * (percent / 100.0f), 0, rectBottom->width);
            break;
        case RIGHT_TO_LEFT:
            rectTop->width = Clamp(rectBottom->width - (rectBottom->width * (percent / 100.0f)), 0, rectBottom->width);
            break;
    }
}


void engine::Bar::draw(float x, float y) {
    if (outlineSize > 0) {
        rectOutline->Draw(colorOutline);
    }
    rectBottom->Draw(colorRight);
    rectTop->Draw(colorLeft);
}

float engine::Bar::getIntersection() const {
    return rectTop->width;
}