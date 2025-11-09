#pragma once

#include <nlohmann/json.hpp>

#include "../engine/group.hpp"
#include "character.hpp"

namespace funkin {
class Stage final : public engine::Group<engine::Object> {
   protected:
    nlohmann::json parsedStage;

   public:
    Stage(const std::string &name,std::shared_ptr<funkin::Character> boyfriend, std::shared_ptr<funkin::Character> dad, std::shared_ptr<funkin::Character> girlfriend,
          float x = 0.0f, float y = 0.0f);

    ~Stage() override;

    std::string name = "stage";
    float zoom = 1.0f;
};
}  // namespace funkin
