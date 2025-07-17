#pragma once

#include "raylib-cpp.hpp"

class note
{
private:
    Texture texture;

public:
    note(Texture texture, double strumTime, int lane, double speed);
    ~note();

    void draw();
    bool isOnScreen();

    int x;
    int y;

    Color color;

    double strumTime;
    int lane;
    double speed;
    double time;
};