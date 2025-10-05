#pragma once

#include "sprite.hpp"
#include "axes.hpp"

namespace engine
{
    class Text : public Sprite
    {
    private:
        raylib::Text *_text;

    protected:
        virtual void draw();

    public:
        Text(std::string text, float size, float x, float y);
        ~Text();


        raylib::Color outlineColor = BLACK;
        raylib::Font font;
        std::string text = "";
        float outlineSize = 0.0f;
        float size = 24.0f;
        float spacing = 1.0f;

        void screenCenter();
        void screenCenter(engine::Axes axes);
    };
}