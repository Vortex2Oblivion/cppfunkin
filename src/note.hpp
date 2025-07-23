#pragma once

#include "sprite.hpp"
#include "strumnote.hpp"


class note : public sprite
{
private:
    strumnote *strum;

public:
    note(double strumTime, int lane, double speed, strumnote *strum);
    virtual ~note();
    virtual void update(double delta);

    double strumTime;
    int lane;
    double speed;
    double songPos;
};