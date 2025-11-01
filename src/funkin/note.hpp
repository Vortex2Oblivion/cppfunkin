#pragma once

#include "../engine/sparrowsprite.hpp"
#include "strumnote.hpp"

namespace funkin {
class Note : public engine::SparrowSprite {
   public:
    Note(float strumTime, int lane, float speed);
    virtual ~Note();
    virtual void update(float delta);

    void updateY(float songPosition);

    float strumTime = 0.0f;
    int lane = 0;
    float speed = 1.0f;
    float sustainLength = 0.0f;

    bool canBeHit;
    bool isPlayer;
    bool wasMissed = false;
    bool isSustain;
};
}  // namespace funkin
