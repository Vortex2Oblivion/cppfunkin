#include "state.hpp"
#include <algorithm>

state::state(/* args */)
{
}

state::~state()
{
}

void state::remove(object *obj)
{
    members.erase(find(members.begin(), members.end(), obj));
    delete obj;
}

void state::add(object *obj)
{
    members.push_back(obj);
}

void state::update(double delta)
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