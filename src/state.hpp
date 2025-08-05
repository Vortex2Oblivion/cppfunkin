#pragma once
#include "object.hpp"
#include <vector>



namespace funkin
{

    class State
    {
    private:
        /* data */
        std::vector<Object *> members;

    public:
        State(/* args */);
        virtual ~State();
        void remove(Object *obj);
        void add(Object *obj);
        void addToFront(Object *obj);
        virtual void update(double delta);
    };
}