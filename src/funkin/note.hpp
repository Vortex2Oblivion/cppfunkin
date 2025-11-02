#pragma once

#include "../engine/sparrowsprite.hpp"
#include "strumnote.hpp"

namespace funkin {
class Note final : public engine::SparrowSprite {
   public:
    Note(float strumTime, int lane, float speed);
    ~Note() override;
    void update(float delta) override;

    void updateY(float songPosition);

    float strumTime = 0.0f;
    int lane = 0;
    float speed = 1.0f;
    float sustainLength = 0.0f;

    bool canBeHit = false;
    bool isPlayer = false;
    bool wasMissed = false;
    bool wasHit = false;
    bool isSustain = false;

    funkin::Note* parentNote = nullptr;
};
}  // namespace funkin
