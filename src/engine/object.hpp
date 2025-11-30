#pragma once

#include <camera.hpp>
#include <memory>

namespace engine {
class Object {
   public:
    explicit Object(float x = 0.0f, float y = 0.0f);
    virtual ~Object();
    virtual void update(float delta);
    virtual void draw(float x = 0.0f, float y = 0.0f);
    raylib::Vector2 position = raylib::Vector2::Zero();
    raylib::Vector2 scrollFactor = raylib::Vector2::One();
    std::shared_ptr<engine::Camera> camera = nullptr;
    bool alive = true;

    static int instances;
};
}  // namespace engine