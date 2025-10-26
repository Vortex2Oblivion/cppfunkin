#pragma once

#include <nlohmann/json.hpp>

#include "../engine/group.hpp"
#include "character.hpp"

namespace funkin {
class Stage : public engine::Group<engine::Object> {
   protected:
    nlohmann::json parsedStage;

   public:
    Stage(std::string name, funkin::Character* boyfriend, funkin::Character* dad, float x = 0.0f, float y = 0.0f);
    ~Stage();

    std::string name = "stage";
    float zoom = 1.0f;
};
}  // namespace funkin
