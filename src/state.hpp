#pragma once
#include "object.hpp"
#include <vector>

namespace funkin
{

    class State : public Object
    {

    public:
        State(/* args */);
        virtual ~State();
        virtual void remove(Object *obj);
        virtual void add(Object *obj);
        virtual void update(double delta);
        virtual void addToFront(Object *obj);
        std::vector<Object *> members;
    };
}