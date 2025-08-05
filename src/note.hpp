#pragma once

#include "sprite.hpp"
#include "strumnote.hpp"

namespace funkin
{
    class Note : public Sprite
    {
    private:
        StrumNote *strum;

    public:
        Note(double strumTime, int lane, double speed, StrumNote *strum);
        virtual ~Note();
        virtual void update(double delta);

        double strumTime;
        int lane;
        double speed;
        double songPos;

        bool canBeHit;
        bool isPlayer;
    };
}