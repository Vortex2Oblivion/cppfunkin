#pragma once
#include "group.hpp"
#include <vector>

namespace engine
{

    class State : public Group<Object>
    {

    public:
        State();
        virtual ~State();
        virtual void create();
        bool initalized = false;
    };
}