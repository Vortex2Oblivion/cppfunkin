#include <raylib-cpp.hpp>

#include "engine/game.hpp"
#include "funkin/songselectstate.hpp"

int main()
{
    raylib::Window window = raylib::Window(1280, 720, "cppfunkin");
    //window.SetTargetFPS(GetMonitorRefreshRate(window.GetMonitor()) * 2);
    raylib::AudioDevice audioDevice = raylib::AudioDevice();

    engine::Game::start(new funkin::SongSelectState());

    raylib::Text fpsCounter("0 FPS", 20.0f, GREEN, GetFontDefault(), 2.0f);

    while (!window.ShouldClose())
    {
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        engine::Game::update(window.GetFrameTime());
        fpsCounter.SetText(TextFormat("%d FPS", ::GetFPS()));
        fpsCounter.Draw(10, 10);
        window.EndDrawing();
    }

    return 0;
}