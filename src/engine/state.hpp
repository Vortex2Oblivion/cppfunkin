#pragma once
#include <vector>

#include "group.hpp"

namespace engine {

class State : public Group<Object> {
   public:
    State();
    ~State() override;
    virtual void create();
    bool initialized = false;
};
}  // namespace engine