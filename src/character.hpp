#pragma once

#include "sparrowsprite.hpp"

namespace funkin
{
    class Character : public SparrowSprite
    {
    private:
        /* data */
    public:
        Character(double x, double y, std::string charName);
        ~Character();
    };
}