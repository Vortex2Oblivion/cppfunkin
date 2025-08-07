#pragma once
#include <vector>
#include "frame.hpp"

namespace funkin
{
    class Animation
    {
    public:
        Animation(std::vector<funkin::Frame *> frames);
        ~Animation();
        std::vector<funkin::Frame *> frames = {};
    };

}