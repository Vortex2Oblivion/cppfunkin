#pragma once

#include "sparrowsprite.hpp"

namespace funkin
{

    class StrumNote : public SparrowSprite
    {
    private:
        /* data */
    public:
        StrumNote(double x, double y, int lane, bool player);
        virtual ~StrumNote();
        void setPosition();

        int lane;
        bool player;
    };
}