#pragma once

#include "../engine/state.hpp"
#include "conductor.hpp"

namespace funkin {
class MusicBeatState : public engine::State {
   protected:
    std::shared_ptr<funkin::Conductor> conductor;

   public:
    MusicBeatState();
    ~MusicBeatState() override;
    void create() override;
    void update(float delta) override;
    virtual void stepHit();
    virtual void beatHit();
};
}  // namespace funkin
