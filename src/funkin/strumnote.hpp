#pragma once

#include "../engine/sparrowsprite.hpp"

namespace funkin {

class StrumNote final : public engine::SparrowSprite {
   private:
    /* data */
   public:
    StrumNote(float x, float y, int lane, bool player);

    ~StrumNote() override;
    void setPosition();

    int lane;
    bool player;
};
}  // namespace funkin