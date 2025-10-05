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
        void update(float delta);
        void draw();
    };

} // namespace engine
