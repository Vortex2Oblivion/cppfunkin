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
        void setText(std::string text);
        void setFont(std::string fileName);
        void setFont(::Font font);
        void screenCenter();
    };
}