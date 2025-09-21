#include "text.hpp"

funkin::Text::Text(std::string text, float size, float x, float y) : Sprite(x, y)
{
    _text = new raylib::Text(text, size);
    _text->spacing = 1.0f;
    this->text = text;
    this->size = size;
}

funkin::Text::~Text()
{
}

void funkin::Text::draw()
{
    _text->text = text;
    _text->Draw(position, angle);
}

void funkin::Text::screenCenter()
{
    position.x = (GetScreenWidth() - _text->MeasureEx().x) / 2;
}