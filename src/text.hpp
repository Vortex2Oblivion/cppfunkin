#pragma once

#include "sprite.hpp"

namespace funkin
{
    class Text : public Sprite
    {
    private:
        raylib::Text* _text;
    protected:
        virtual void draw();
        
        public:
        Text(std::string text, float size, float x, float y);
        ~Text();
        std::string text = "";
        float size = 8.0f;
        void screenCenter();
    };
}