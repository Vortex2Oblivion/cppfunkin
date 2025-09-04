#pragma once

#include "sparrowsprite.hpp"

namespace funkin
{

    class StrumNote : public SparrowSprite
    {
    private:
        /* data */
    public:
        StrumNote(float x, float y, int lane, bool player);
        virtual ~StrumNote();
        void setPosition();

        int lane;
        bool player;
    };
}