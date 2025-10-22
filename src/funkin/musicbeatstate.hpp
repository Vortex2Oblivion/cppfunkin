#pragma once

#include "../engine/state.hpp"
#include "conductor.hpp"

namespace funkin {
class MusicBeatState : public engine::State {
   private:
    /* data */
   protected:
    Conductor* conductor;

   public:
    MusicBeatState(/* args */);
    ~MusicBeatState();
    virtual void create();
    virtual void update(float delta);
    virtual void stepHit();
    virtual void beatHit();
};
}  // namespace funkin
