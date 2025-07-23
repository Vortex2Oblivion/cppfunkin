#pragma once

#include "sprite.hpp"

class strumnote : public sprite
{
private:
    /* data */
public:
    strumnote(double x, double y, int lane, bool player);
    virtual ~strumnote();
    void setPosition();

    int lane;
    bool player;
};