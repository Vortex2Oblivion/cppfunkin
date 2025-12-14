#pragma once

#include "axes.hpp"
#include "sprite.hpp"

#include <cstdint>

namespace engine {
enum FillDirection {
    LEFT_TO_RIGHT,
    RIGHT_TO_LEFT,
};

class Bar final : public Sprite {
   private:
    /* data */
    std::unique_ptr<raylib::Rectangle> rectOutline;
    std::unique_ptr<raylib::Rectangle>rectBottom;
    std::unique_ptr<raylib::Rectangle> rectTop;

   public:
    Bar(float x, float y, float width, float height, raylib::Color colorLeft, raylib::Color colorRight, float outlineSize = 0,
        raylib::Color colorOutline = raylib::Color::Black());
    ~Bar() override;
    void screenCenter(engine::Axes axes) override;
    void update(float delta) override;
    void draw(float x, float y) override;

    [[nodiscard]] float getIntersection() const;

    raylib::Color colorOutline;
    raylib::Color colorLeft;
    raylib::Color colorRight;

    engine::FillDirection fillDirection = LEFT_TO_RIGHT;

    raylib::Vector2 origin;

    float percent = 50.0f;
    float outlineSize = 0.0f;
};

}  // namespace engine
