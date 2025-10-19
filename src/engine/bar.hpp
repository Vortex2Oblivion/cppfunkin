#pragma once

#include "sprite.hpp"
#include "axes.hpp"

namespace engine
{
    class Bar : public Sprite
    {
    private:
        /* data */
        raylib::Rectangle *rectOutline;
        raylib::Rectangle *rectBottom;
        raylib::Rectangle *rectTop;

    public:
        Bar(float x, float y, float width, float height, raylib::Color colorLeft, raylib::Color colorRight, unsigned int outlineSize = 0, raylib::Color colorOutline = raylib::Color::Black());
        ~Bar();
        void screenCenter();
        void screenCenter(engine::Axes axes);
        void update(float delta);
        void draw();

        raylib::Color colorOutline;
        raylib::Color colorLeft;
        raylib::Color colorRight;

        raylib::Vector2 origin;

        float percent = 50.0f;
        unsigned int outlineSize = 0;
    };

} // namespace engine
