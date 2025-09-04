#pragma once

#include "sparrowsprite.hpp"
#include "strumnote.hpp"

namespace funkin
{
    class Note : public SparrowSprite
    {
    private:
        StrumNote *strum;

    public:
        Note(float strumTime, int lane, float speed, StrumNote *strum);
        virtual ~Note();
        virtual void update(float delta);

        float strumTime;
        int lane;
        float speed;
        float songPos;

        bool canBeHit;
        bool isPlayer;
    };
}