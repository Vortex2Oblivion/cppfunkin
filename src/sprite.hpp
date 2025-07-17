#pragma once

#include <raylib-cpp.hpp>
#include <string>

#include "object.hpp"

using namespace std;

class sprite : public object
{
private:
    virtual void draw();
    raylib::Texture texture;
    raylib::Rectangle source;
    raylib::Rectangle dest;
public:
    sprite(double x, double y);
    virtual ~sprite();
    void loadGraphic(string path);
    void loadGraphic(raylib::Texture tex);
    virtual void update(double delta);
    bool isOnScreen();

    raylib::Vector2 origin;
    double angle;
    raylib::Color color;
};