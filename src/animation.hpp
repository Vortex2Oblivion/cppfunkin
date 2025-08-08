#pragma once
#include <vector>
#include "frame.hpp"

namespace funkin
{
    class Animation
    {
    private:
        int frameCounter = 0;

    public:
        Animation(std::vector<funkin::Frame *> frames, int framerate);
        ~Animation();
        std::vector<funkin::Frame *> frames = {};
        int framerate = 24;
        int currentFrame = 0;
        void update(double delta);
    };

}