#include "state.hpp"
#include <algorithm>

engine::State::State(/* args */) : Object(0, 0)
{
}

engine::State::~State()
{
    for (auto member : members)
    {
        remove(member);
    }
}

void engine::State::remove(Object *obj)
{
    obj->alive = false;
    members.erase(find(members.begin(), members.end(), obj));
    if (obj != nullptr)
    {
        delete obj;
    }
}

void engine::State::addToFront(Object *obj)
{
    members.insert(members.begin(), obj);
}

void engine::State::add(Object *obj)
{
    members.push_back(obj);
}

void engine::State::update(float delta)
{
    for (auto member : members)
    {
        if (member == nullptr || !member->alive)
        {
            continue;
        }
        member->update(delta);
    }
}