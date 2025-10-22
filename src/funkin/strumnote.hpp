#pragma once

#include "../engine/sparrowsprite.hpp"

namespace funkin {

class StrumNote : public engine::SparrowSprite {
   private:
    /* data */
   public:
    StrumNote(float x, float y, int lane, bool player);
    virtual ~StrumNote();
    void setPosition();

    int lane;
    bool player;
};
}  // namespace funkin