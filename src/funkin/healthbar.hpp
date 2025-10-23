#pragma once

#include "../engine/bar.hpp"
#include "../engine/group.hpp"

#include "healthicon.hpp"

namespace funkin {
class HealthBar : public engine::Group<engine::Object> {
   private:
    /* data */
   public:
    HealthBar(float x, float y, std::string iconLeft, std::string iconRight, raylib::Color colorLeft, raylib::Color colorRight);
    ~HealthBar();
    void update(float delta);
    void bopIcons(float scaleFactor);
    engine::Bar* bar;
    funkin::HealthIcon* iconP1;
    funkin::HealthIcon* iconP2;
};

}  // namespace  funkin
