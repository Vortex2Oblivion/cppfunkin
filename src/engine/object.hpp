#pragma once

#include <raylib-cpp.hpp>
#include "../engine/camera.hpp"

namespace engine {
class Object {
   public:
    Object(float x = 0.0f, float y = 0.0f);
    virtual ~Object();
    virtual void update(float delta);
    virtual void draw(float x = 0.0f, float y = 0.0f);
    raylib::Vector2 position;
    raylib::Vector2 scrollFactor;
    engine::Camera* camera;
    bool alive = true;
};
}  // namespace engine