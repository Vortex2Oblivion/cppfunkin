#pragma once
#include "object.hpp"
#include <vector>

using namespace std;

class state
{
private:
    /* data */
    vector<object *> members;

public:
    state(/* args */);
    virtual ~state();
    void remove(object *obj);
    void add(object *obj);
    void addToFront(object* obj);
    virtual void update(double delta);
};