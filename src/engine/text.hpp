#pragma once

#include "axes.hpp"
#include "sprite.hpp"
#include <memory>

namespace engine {
class Text : public Sprite {
   private:
    std::unique_ptr<raylib::Text> _text;

   public:
     Text(const std::string &text, float size, float x, float y);
     ~Text() override;

    raylib::Color outlineColor = BLACK;
    raylib::Font font;
    std::string text;
    float outlineSize = 0.0f;
    float size = 24.0f;
    float spacing = 1.0f;

    void draw(float x, float y) override;
    void screenCenter(engine::Axes axes = engine::Axes::XY) override;
};
}  // namespace engine