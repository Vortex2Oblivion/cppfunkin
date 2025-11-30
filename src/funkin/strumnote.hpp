#pragma once

#include "../engine/sparrowsprite.hpp"

namespace funkin {

class StrumNote final : public engine::SparrowSprite {
   private:
    /* data */
   public:
    StrumNote(float x, float y, int lane);

    ~StrumNote() override;
    void setPosition();

    int lane;
};
}  // namespace funkin