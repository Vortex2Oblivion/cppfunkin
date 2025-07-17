#include "raylib-cpp.hpp"

#include "note.hpp"


note::note(Texture texture, double strumTime, int lane, double speed)
{
    this->texture = texture;
    this->strumTime = strumTime;
    this->lane = lane;
    this->speed = speed;
}

note::~note()
{
}

void note::draw()
{
    x = 100 * lane;
    y = -0.45 * (time * 1000 - strumTime) * speed;
    if (isOnScreen())
    {
        DrawTexture(texture, x, y, color);
    }
}

bool note::isOnScreen()
{
    return !((y + texture.height < 0 || y > GetScreenHeight()) || (x + texture.width < 0 || x > GetScreenWidth()));
}
