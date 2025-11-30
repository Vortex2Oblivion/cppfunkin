#pragma once

#include "frame.hpp"

#include <cstdint>
#include <memory>
#include <vector>

namespace engine {
class Animation {
   private:
    float frameTimer = 0.0f;

   public:
    Animation(const std::vector<std::shared_ptr<engine::Frame>> &frames, uint8_t framerate, const std::string &name, bool looped = false);
    ~Animation();
    std::vector<std::shared_ptr<engine::Frame>> frames = {};
    uint8_t framerate = 24;
    size_t currentFrame = 0;
    bool looped = false;
    void update(float delta);
    void resetFrame();

    [[nodiscard]] bool isFinished() const;

    std::string name;
    float animationTimer = 0.0f;
};

}  // namespace engine