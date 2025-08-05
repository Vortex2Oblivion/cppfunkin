#pragma once

#include "sprite.hpp"

namespace funkin
{

    class StrumNote : public Sprite
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