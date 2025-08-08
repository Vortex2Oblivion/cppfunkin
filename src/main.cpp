#include <raylib-cpp.hpp>

#include "game.hpp"
#include "playstate.hpp"

int main()
{
    raylib::Window window = raylib::Window(1280, 720, "cppfunkin");
    raylib::AudioDevice audioDevice = raylib::AudioDevice();

    funkin::Game funkin = funkin::Game(new funkin::PlayState());

    while (!window.ShouldClose())
    {
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        funkin.update(window.GetFrameTime());
        window.DrawFPS();
        window.EndDrawing();
    }

    return 0;
}