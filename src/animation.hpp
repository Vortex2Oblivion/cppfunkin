#pragma once
#include <vector>
#include "frame.hpp"

namespace funkin
{
    class Animation
    {
    public:
        Animation(std::vector<funkin::Frame *> frames, int framerate);
        ~Animation();
        std::vector<funkin::Frame *> frames = {};
        int framerate;
    };

}