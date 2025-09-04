#pragma once

#include "state.hpp"
#include "conductor.hpp"

namespace funkin
{
    class MusicBeatState : public State
    {
    private:
        /* data */
    protected:
        Conductor *conductor = new Conductor();

    public:
        MusicBeatState(/* args */);
        ~MusicBeatState();
        virtual void update(float delta);
        virtual void stepHit();
        virtual void beatHit();
    };
} // namespace funkin
