#pragma once
#include <vector>
#include <cstdint>

#include "frame.hpp"

namespace funkin
{
    class Animation
    {
    private:
        float frameTimer = 0.0;

    public:
        Animation(std::vector<funkin::Frame *> frames, uint8_t framerate);
        ~Animation();
        std::vector<funkin::Frame *> frames = {};
        uint8_t framerate = 24;
        size_t currentFrame = 0;
        void update(float delta);
        void resetFrame(void);
    };

}