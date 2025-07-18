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
    ~state();
    void add(object *obj);
    virtual void update(double delta);
};