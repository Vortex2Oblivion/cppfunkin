#pragma once

#include <raylib-cpp.hpp>
#include <string>

#include "object.hpp"
#include <map>


namespace funkin
{
    class Sprite : public Object
    {
    private:
        virtual void draw();
        raylib::Texture *texture;
        raylib::Rectangle source;
        raylib::Rectangle dest;
        static std::map<std::string, raylib::Texture *> texturePool;

    public:
        Sprite(double x, double y);
        virtual ~Sprite();
        void loadGraphic(std::string path);
        virtual void update(double delta);
        bool isOnScreen();

        raylib::Vector2 origin;
        double angle;
        raylib::Color color;
    };
}