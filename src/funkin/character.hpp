#pragma once

#include "../engine/sparrowsprite.hpp"

namespace funkin {
class Character final : public engine::SparrowSprite {
   protected:
    bool danceLeft = true;
   public:
    Character(float x, float y, std::string characterName, bool isPlayer);

    ~Character() override;
    void dance();

    std::string characterName;
    raylib::Vector2 cameraOffset = raylib::Vector2::Zero();
};
}  // namespace funkin