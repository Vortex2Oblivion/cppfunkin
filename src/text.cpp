#include "text.hpp"

funkin::Text::Text(std::string text, float size, float x, float y) : Sprite(x, y)
{
    _text = new raylib::Text(text, size);
    _text->spacing = 1.0f;
}

funkin::Text::~Text()
{
    UnloadFont(_text->font);
    delete _text;
}

void funkin::Text::draw()
{
    _text->Draw(position, angle);
}

void funkin::Text::setText(std::string text)
{
    _text->text = text;
}

void funkin::Text::setFont(std::string fileName)
{
    _text->font = LoadFont(fileName.c_str());
}

void funkin::Text::setFont(::Font font)
{
    _text->font = font;
}

void funkin::Text::screenCenter()
{
    position.x = (GetScreenWidth() - _text->MeasureEx().x) / 2;
}