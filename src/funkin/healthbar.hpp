#pragma once

#include "healthicon.hpp"
#include <bar.hpp>
#include <group.hpp>

namespace funkin {
class HealthBar : public engine::Group<engine::Object> {
   private:
    /* data */
   public:
    HealthBar(float x, float y, std::string iconLeft, std::string iconRight, raylib::Color colorLeft, raylib::Color colorRight);
    ~HealthBar() override;
    void update(float delta) override;

    void bopIcons(float scaleFactor) const;
    std::shared_ptr<engine::Bar> bar;
    std::shared_ptr<funkin::HealthIcon> iconP1;
    std::shared_ptr<funkin::HealthIcon> iconP2;
};

}  // namespace  funkin
