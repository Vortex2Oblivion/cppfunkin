#pragma once

#include "../engine/group.hpp"

namespace funkin
{
    class PlayField : public engine::Group
    {
    private:
        /* data */
    public:
        PlayField(/* args */);
        ~PlayField();
        bool cpuControlled = true;
        engine::Group notes;
    };
} // namespace funkin
