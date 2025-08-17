#include <raylib-cpp.hpp>

#include "game.hpp"
#include "playstate.hpp"
#include "songselectstate.hpp"

int main()
{
    raylib::Window window = raylib::Window(1280, 720, "cppfunkin");
    window.SetTargetFPS(GetMonitorRefreshRate(window.GetMonitor()) * 2);
    raylib::AudioDevice audioDevice = raylib::AudioDevice();

    funkin::Game::start(new funkin::SongSelectState());

    while (!window.ShouldClose())
    {
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        funkin::Game::update(window.GetFrameTime());
        window.DrawFPS();
        window.EndDrawing();
    }

    return 0;
}