#include <raylib-cpp.hpp>

#include "engine/game.hpp"
#include "funkin/songselectstate.hpp"

int main() {
    int windowWidth = 1280;
    int windowHeight = 720;
    raylib::Window window = raylib::Window(windowWidth, windowHeight, "Friday Night Funkin'");
    window.SetTargetFPS(GetMonitorRefreshRate(window.GetMonitor()) * 2);

    raylib::Image iconOG = raylib::Image("assets/images/iconOG.png");
    window.SetIcon(iconOG);
    iconOG.Unload();

    raylib::AudioDevice audioDevice = raylib::AudioDevice();

    engine::Game::start(new funkin::SongSelectState());

    while (!window.ShouldClose()) {
        if (IsKeyPressed(KEY_F11)) {
            window.ToggleFullscreen();
        }
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        engine::Game::update(window.GetFrameTime());
        window.DrawFPS(10, 10);
        window.EndDrawing();
    }

    return 0;
}
