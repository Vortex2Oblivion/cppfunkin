#include "state.hpp"
#include <algorithm>

funkin::State::State(/* args */) : Object(0, 0)
{
}

funkin::State::~State()
{
    for (auto member : members)
    {
        remove(member);
    }
}

void funkin::State::remove(Object *obj)
{
    members.erase(find(members.begin(), members.end(), obj));
    delete obj;
}

void funkin::State::addToFront(Object *obj)
{
    members.insert(members.begin(), obj);
}

void funkin::State::add(Object *obj)
{
    members.push_back(obj);
}

void funkin::State::update(double delta)
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