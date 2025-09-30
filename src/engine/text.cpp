#include "text.hpp"

engine::Text::Text(std::string text, float size, float x, float y) : Sprite(x, y)
{
    _text = new raylib::Text(text, size);
    _text->spacing = 1.0f;
}

engine::Text::~Text()
{
    UnloadFont(_text->font);
    delete _text;
}

void engine::Text::draw()
{
    _text->Draw(position, angle);
}

void engine::Text::setText(std::string text)
{
    _text->text = text;
}

void engine::Text::setFont(std::string fileName)
{
    _text->font = LoadFont(fileName.c_str());
}

void engine::Text::setFont(::Font font)
{
    _text->font = font;
}

void engine::Text::screenCenter()
{
    position.x = (GetScreenWidth() - _text->MeasureEx().x) / 2;
}