#pragma once

#include "../engine/sparrowsprite.hpp"

namespace funkin {
class Character : public engine::SparrowSprite {
   private:
    /* data */
   public:
    Character(float x, float y, std::string charName);
    ~Character();
    void dance();
};
}  // namespace funkin