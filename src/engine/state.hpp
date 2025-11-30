#pragma once

#include "group.hpp"

namespace engine {

class State : public engine::Group<engine::Object> {
   public:
    State();
    ~State() override;
    virtual void create();
    bool initialized = false;
};
}  // namespace engine