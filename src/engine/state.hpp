#pragma once
#include <vector>

#include "group.hpp"

namespace engine {

class State : public Group<Object> {
   public:
    State();
    virtual ~State();
    virtual void create();
    bool initalized = false;
};
}  // namespace engine