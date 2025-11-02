#pragma once
#include <cstdint>
#include <vector>

#include "frame.hpp"

namespace engine {
class Animation {
   private:
    float frameTimer = 0.0f;

   public:
    Animation(const std::vector<engine::Frame*> &frames, uint8_t framerate, const std::string &name);
    ~Animation();
    std::vector<engine::Frame*> frames = {};
    uint8_t framerate = 24;
    size_t currentFrame = 0;
    void update(float delta);
    void resetFrame();

    [[nodiscard]] bool isFinished() const;

    std::string name;
    float animationTimer = 0.0f;
};

}  // namespace engine