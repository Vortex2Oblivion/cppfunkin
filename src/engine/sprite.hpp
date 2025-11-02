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
    static void cacheTexture(std::string path);

   protected:
    raylib::Texture* texture = nullptr;
    raylib::Rectangle source = raylib::Rectangle();
    raylib::Rectangle dest = raylib::Rectangle();

    void calculateScrollFactor();

   public:
    Sprite(float x, float y);
    ~Sprite() override;
    void loadGraphic(const std::string &path);
    void update(float delta) override;
    virtual bool isOnScreen(float x = 0.0f, float y = 0.0f);

    virtual raylib::Vector2 getMidpoint();
    virtual void screenCenter();
    virtual void screenCenter(engine::Axes axes);
    void draw(float x = 0.0f, float y = 0.0f) override;
    virtual void centerOrigin();

    raylib::Vector2 origin = raylib::Vector2();
    raylib::Vector2 scale = raylib::Vector2(1.0f, 1.0f);
    raylib::Vector2 offset = raylib::Vector2();
    float angle = 0.0f;
    raylib::Color color = WHITE;
    bool flipX = false;

    static void clearTextureCache();
};
}  // namespace engine
