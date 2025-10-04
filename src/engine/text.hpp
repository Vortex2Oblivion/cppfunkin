#pragma once

#include "sprite.hpp"

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


        Font font;
        std::string text = "";
        float outlineSize = 0.0f;
        float size = 24.0f;
        float spacing = 1.0f;

        void screenCenter();
    };
}