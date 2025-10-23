#pragma once

#include "../engine/sparrowsprite.hpp"

namespace funkin {
class Character : public engine::SparrowSprite {
   private:
    /* data */
   public:
    Character(float x, float y, std::string characterName);
    ~Character();
    void dance();

    std::string characterName;
};
}  // namespace funkin