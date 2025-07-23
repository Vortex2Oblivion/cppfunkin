#include "state.hpp"

state::state(/* args */)
{
}

state::~state()
{
}

void state::add(object* obj){
    members.push_back(obj);
}

void state::update(double delta){
    for(auto member : members){
        if(!member->alive){
            continue;
        }
        member->update(delta);
    }
}