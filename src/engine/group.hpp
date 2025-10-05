#pragma once

#include "object.hpp"

namespace engine
{
    class Group : public Object
    {
    private:
        /* data */
    public:
        std::vector<Object *> members = {};
        Group(/* args */);
        Group(float x, float y);
        ~Group();
        virtual void remove(Object *obj);
        virtual void add(Object *obj);
        virtual void update(float delta);
        virtual void draw();
        virtual void addToFront(Object *obj);
    };

} // namespace engine
