#include "text.hpp"

engine::Text::Text(std::string text, float size, float x, float y) : Sprite(x, y)
{
    _text = new raylib::Text(text, size, WHITE, GetFontDefault(), 1.0f);
    origin = _text->MeasureEx() / 2.0f;
    this->size = size;
}

engine::Text::~Text()
{
    UnloadFont(_text->font);
    delete _text;
}

void engine::Text::draw()
{
    // TODO: replace with shader maybe?
    if (outlineSize > 0)
    {
        _text->Draw(font, text, position + raylib::Vector2(-outlineSize, 0), origin, angle, size, spacing, BLACK);
        _text->Draw(font, text, position + raylib::Vector2(-outlineSize, outlineSize), origin, angle, size, spacing, BLACK);
        _text->Draw(font, text, position + raylib::Vector2(0, outlineSize), origin, angle, size, spacing, BLACK);
        _text->Draw(font, text, position + raylib::Vector2(outlineSize, outlineSize), origin, angle, size, spacing, BLACK);
        _text->Draw(font, text, position + raylib::Vector2(outlineSize, 0), origin, angle, size, spacing, BLACK);
        _text->Draw(font, text, position + raylib::Vector2(-outlineSize, -outlineSize), origin, angle, size, spacing, BLACK);
        _text->Draw(font, text, position + raylib::Vector2(0, -outlineSize), origin, angle, size, spacing, BLACK);
    }
    _text->Draw(font, text, position, origin, angle, size, spacing, color);
}

void engine::Text::screenCenter()
{
    position.x = (GetScreenWidth() - _text->MeasureEx().x) / 2;
}