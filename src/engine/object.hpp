#pragma once

#include <raylib-cpp.hpp>

namespace engine {
class Object {
   public:
    Object(float x = 0.0f, float y = 0.0f);
    virtual ~Object();
    virtual void update(float delta);
    virtual void draw();
    virtual void draw(float x, float y);
    raylib::Vector2 position;
    raylib::Camera2D* camera;
    bool alive = true;
};
}  // namespace engine