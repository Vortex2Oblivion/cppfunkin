#pragma once

#include "conductor.hpp"
#include "../engine/state.hpp"

namespace funkin
{
    class MusicBeatState : public engine::State
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
