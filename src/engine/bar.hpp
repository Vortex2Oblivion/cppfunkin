#pragma once

#include "axes.hpp"
#include "sprite.hpp"

namespace engine {
enum FillDirection {
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT,
};

class Bar final : public Sprite {
   private:
    /* data */
    raylib::Rectangle* rectOutline;
    raylib::Rectangle* rectBottom;
    raylib::Rectangle* rectTop;

   public:
    Bar(float x, float y, float width, float height, raylib::Color colorLeft, raylib::Color colorRight, unsigned int outlineSize = 0,
        raylib::Color colorOutline = raylib::Color::Black());
    ~Bar() override;
    void screenCenter() override;
    void screenCenter(engine::Axes axes) override;
    void update(float delta) override;
    void draw(float x, float y) override;

    float getIntersection();

    raylib::Color colorOutline;
    raylib::Color colorLeft;
    raylib::Color colorRight;

    engine::FillDirection fillDirection;

    raylib::Vector2 origin;

    float percent = 50.0f;
    unsigned int outlineSize = 0;
};

}  // namespace engine
