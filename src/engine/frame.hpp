#pragma once

#include <raylib-cpp.hpp>

namespace engine {
class Frame {
   private:
    /* data */
   public:
    explicit Frame(raylib::Rectangle rect);
    Frame(raylib::Rectangle rect, raylib::Vector2 sourceSize, raylib::Vector2 offset);
    Frame(float x, float y, float width, float height, float frameX, float frameY, float frameWidth, float frameHeight);
    ~Frame();

    float x;
    float y;
    float width;
    float height;
    float frameX;
    float frameY;
    float frameWidth;
    float frameHeight;

    bool exists = false;
};
}  // namespace engine