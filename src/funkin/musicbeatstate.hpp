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
    ~MusicBeatState() override;
    void create() override;
    void update(float delta) override;
    virtual void stepHit();
    virtual void beatHit();
};
}  // namespace funkin
