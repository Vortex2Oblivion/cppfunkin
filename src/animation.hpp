#pragma once
#include <vector>
#include "frame.hpp"

namespace funkin
{
    class Animation
    {
    private:
        double frameTimer = 0.0;

    public:
        Animation(std::vector<funkin::Frame *> frames, int framerate);
        ~Animation();
        std::vector<funkin::Frame *> frames = {};
        uint8_t framerate = 24;
        uint8_t currentFrame = 0;
        void update(double delta);
        void resetFrame(void);
    };

}