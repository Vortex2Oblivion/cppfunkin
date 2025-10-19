#include "bar.hpp"
#include "axes.hpp"

engine::Bar::Bar(float x, float y, float width, float height, raylib::Color colorLeft, raylib::Color colorRight, unsigned int outlineSize, raylib::Color colorOutline) : Sprite(x, y)
{
    rectBottom = new raylib::Rectangle(x, y, width, height);
    rectTop = new raylib::Rectangle(x, y, width * (percent / 100.0f), height);
    rectOutline = new raylib::Rectangle(x - outlineSize / 2.0f, y - outlineSize / 2.0f, width + outlineSize, height + outlineSize);
    this->colorLeft = colorLeft;
    this->colorRight = colorRight;
    this->colorOutline = colorOutline;
    this->outlineSize = outlineSize;
    this->origin = raylib::Vector2(rectOutline->width / 2, rectOutline->height / 2);
}

engine::Bar::~Bar()
{
    delete rectBottom;
    delete rectTop;
}

void engine::Bar::screenCenter()
{
    screenCenter(X);
    screenCenter(Y);
}

void engine::Bar::screenCenter(engine::Axes axes)
{
    switch (axes)
    {
    case X:
        position.x = (GetScreenWidth() - rectOutline->width) / 2;
        break;
    case Y:
        position.y = (GetScreenHeight() - rectOutline->height) / 2;
        break;
    default:
        screenCenter();
    }
}

void engine::Bar::update(float delta)
{
    rectTop->x = rectBottom->x = position.x;
    rectTop->y = rectBottom->y = position.y;

    rectOutline->width = rectBottom->x - outlineSize / 2.0f;
    rectOutline->height = rectBottom->y - outlineSize / 2.0f;
    rectOutline->width = rectBottom->width + outlineSize;
    rectOutline->height = rectBottom->height + outlineSize;
    rectOutline->x = rectBottom->x - outlineSize / 2.0f;
    rectOutline->y = rectBottom->y - outlineSize / 2.0f;

    rectTop->width = rectBottom->width * (percent / 100.0f);
}

void engine::Bar::draw()
{
    if (outlineSize > 0)
    {
        rectOutline->Draw(colorOutline);
    }
    rectBottom->Draw(colorRight);
    rectTop->Draw(colorLeft);
}