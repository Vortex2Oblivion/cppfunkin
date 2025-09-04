#pragma once

#include "sparrowsprite.hpp"

namespace funkin
{
    class Character : public SparrowSprite
    {
    private:
        /* data */
    public:
        Character(float x, float y, std::string charName);
        ~Character();
    };
}