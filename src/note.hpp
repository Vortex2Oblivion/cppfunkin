#pragma once

#include "sprite.hpp"

class note : public sprite
{
private:

public:
    note(double strumTime, int lane, double speed);
    virtual ~note();
    virtual void update(double delta);

    double strumTime;
    int lane;
    double speed;
    double songPos;
};