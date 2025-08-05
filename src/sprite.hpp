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
        raylib::Texture *texture;
        static std::map<std::string, raylib::Texture *> texturePool;

    protected:
        virtual void draw();
        raylib::Rectangle source;
        raylib::Rectangle dest;

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