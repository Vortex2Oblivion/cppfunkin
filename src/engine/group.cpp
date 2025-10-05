#include "group.hpp"

engine::Group::Group() : Object()
{
}

engine::Group::Group(float x, float y) : Object(x, y)
{
}

engine::Group::~Group()
{
    members.clear();
}

void engine::Group::draw()
{
}

void engine::Group::remove(Object *obj)
{
    members.erase(find(members.begin(), members.end(), obj));
}

void engine::Group::addToFront(Object *obj)
{
    members.insert(members.begin(), obj);
}

void engine::Group::add(Object *obj)
{
    members.push_back(obj);
}

void engine::Group::update(float delta)
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