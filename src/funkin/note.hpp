#pragma once

#include "../engine/sparrowsprite.hpp"
#include "strumnote.hpp"

namespace funkin {
class Note : public engine::SparrowSprite {
   protected:
    StrumNote* strum;
    Note* sustainNote;

   public:
    Note(float strumTime, int lane, float speed, StrumNote* strum);
    virtual ~Note();
    virtual void update(float delta);

    float strumTime;
    int lane;
    float speed = 1.0f;
    float songPos;
    float sustainLength = 0.0f;

    bool canBeHit;
    bool isPlayer;
    bool wasMissed = false;
    bool isSustain;
};
}  // namespace funkin
