#pragma once

#include <map>
#include <raylib-cpp.hpp>
#include <string>

#include "axes.hpp"
#include "object.hpp"

namespace engine {
class Sprite : public Object {
   private:
    static std::map<std::string, raylib::Texture*> texturePool;

   protected:
    raylib::Texture* texture = nullptr;
    raylib::Rectangle source = raylib::Rectangle();
    raylib::Rectangle dest = raylib::Rectangle();

   public:
    Sprite(float x, float y);
    virtual ~Sprite();
    void loadGraphic(std::string path);
    virtual void update(float delta);
    virtual bool isOnScreen(float x = 0.0f, float y = 0.0f);
    raylib::Vector2 getMidpoint();
    virtual void screenCenter();
    virtual void screenCenter(engine::Axes axes);
    virtual void draw();
    virtual void draw(float x, float y);

    raylib::Vector2 origin = raylib::Vector2();
    raylib::Vector2 scale = raylib::Vector2(1.0f, 1.0f);
    raylib::Vector2 offset = raylib::Vector2();
    float angle = 0.0f;
    raylib::Color color = WHITE;
    bool flipX = false;

    static void clearTextureCache();
};
}  // namespace engine
