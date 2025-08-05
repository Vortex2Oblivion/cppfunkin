#pragma once

#include <raylib-cpp.hpp>
#include <string>

#include "object.hpp"
#include <map>

using namespace std;
namespace funkin
{
    class Sprite : public Object
    {
    private:
        virtual void draw();
        raylib::Texture *texture;
        raylib::Rectangle source;
        raylib::Rectangle dest;
        static map<string, raylib::Texture *> texturePool;

    public:
        Sprite(double x, double y);
        virtual ~Sprite();
        void loadGraphic(string path);
        virtual void update(double delta);
        bool isOnScreen();

        raylib::Vector2 origin;
        double angle;
        raylib::Color color;
    };
}