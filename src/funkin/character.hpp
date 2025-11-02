#pragma once

#include "../engine/sparrowsprite.hpp"

namespace funkin {
class Character : public engine::SparrowSprite {
   private:
    /* data */
   public:
    Character(float x, float y, std::string characterName, bool isPlayer);

    ~Character() override;
    void dance();

    std::string characterName;
    bool danceLeft = true;
    raylib::Vector2 cameraOffset = raylib::Vector2::Zero();
};
}  // namespace funkin