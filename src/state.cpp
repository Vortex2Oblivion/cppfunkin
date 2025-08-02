#include "state.hpp"
#include <algorithm>

state::state(/* args */)
{
}

state::~state()
{
    for(auto member : members){
        remove(member);
    }
}

void state::remove(object *obj)
{
    members.erase(find(members.begin(), members.end(), obj));
    delete obj;
}

void state::addToFront(object *obj)
{
    members.insert(members.begin(), obj);
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