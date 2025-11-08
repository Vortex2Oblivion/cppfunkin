#include <raylib-cpp.hpp>

#include "engine/game.hpp"
#include "funkin/songselectstate.hpp"
#include "raylib.h"

#if __APPLE__
#include "engine/macos.hpp"
#endif

int main() {
    constexpr int windowWidth = 1280;
    constexpr int windowHeight = 720;
    auto window = raylib::Window(windowWidth, windowHeight, "Friday Night Funkin'", FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);

    #if __APPLE__
    MacOSUtil::fixWindowColorSpace();
    #endif

    window.SetTargetFPS(GetMonitorRefreshRate(window.GetMonitor()) * 2);

    auto iconOG = raylib::Image("assets/images/iconOG.png");
    window.SetIcon(iconOG);
    iconOG.Unload();

    auto audioDevice = raylib::AudioDevice();
    audioDevice.SetVolume(0.25f);

    engine::Game(new funkin::SongSelectState());

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
