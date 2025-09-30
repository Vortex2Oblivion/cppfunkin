#pragma once
#include "object.hpp"
#include <vector>

namespace engine
{

    class State : public Object
    {

    public:
        State(/* args */);
        virtual ~State();
        virtual void remove(Object *obj);
        virtual void add(Object *obj);
        virtual void update(float delta);
        virtual void addToFront(Object *obj);
        std::vector<Object *> members;
    };
}