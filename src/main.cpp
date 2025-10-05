#include <raylib-cpp.hpp>

#include "engine/game.hpp"
#include "funkin/songselectstate.hpp"

int main()
{
    raylib::Window window = raylib::Window(1280, 720, "Friday Night Funkin'");
    //window.SetTargetFPS(GetMonitorRefreshRate(window.GetMonitor()) * 2);
    
    raylib::Image iconOG = raylib::Image("assets/images/iconOG.png");
    window.SetIcon(iconOG);
    iconOG.Unload();

    raylib::AudioDevice audioDevice = raylib::AudioDevice();

    engine::Game::start(new funkin::SongSelectState());

    while (!window.ShouldClose())
    {
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        engine::Game::update(window.GetFrameTime());
        window.DrawFPS(10, 10);
        window.EndDrawing();
    }

    return 0;
}
