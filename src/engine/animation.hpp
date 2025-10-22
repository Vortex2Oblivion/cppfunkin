#pragma once
#include <cstdint>
#include <vector>

#include "frame.hpp"

namespace engine {
class Animation {
   private:
    float frameTimer = 0.0;

   public:
    Animation(std::vector<engine::Frame*> frames, uint8_t framerate, std::string name);
    ~Animation();
    std::vector<engine::Frame*> frames;
    uint8_t framerate = 24;
    size_t currentFrame = 0;
    void update(float delta);
    void resetFrame();
    bool isFinished();
    std::string name;
};

}  // namespace engine