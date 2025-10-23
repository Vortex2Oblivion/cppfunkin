#pragma once

#include "../engine/animatedsprite.hpp"

namespace funkin {
class HealthIcon : public engine::AnimatedSprite {
   public:
    HealthIcon(std::string character, float x = 0.0f, float y = 0.0f);
    ~HealthIcon();

    std::string character = "";
};

}  // namespace funkin
