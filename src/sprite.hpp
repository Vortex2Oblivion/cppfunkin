#pragma once

#include <raylib-cpp.hpp>
#include <string>

#include "object.hpp"
#include <map>

using namespace std;

class sprite : public object
{
private:
    virtual void draw();
    raylib::Texture *texture;
    raylib::Rectangle source;
    raylib::Rectangle dest;
    static map<string, raylib::Texture*> texturePool;

public:
    sprite(double x, double y);
    virtual ~sprite();
    void loadGraphic(string path);
    virtual void update(double delta);
    bool isOnScreen();

    raylib::Vector2 origin;
    double angle;
    raylib::Color color;
};