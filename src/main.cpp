#include <raylib-cpp.hpp>

#include "engine/game.hpp"
#include "funkin/songselectstate.hpp"
#include "engine/memorycounter.hpp"

#if __APPLE__
#include "engine/macos.hpp"
#endif
#include <iostream>
#include "funkin/coolutil.hpp"

int main() {
    constexpr int windowWidth = 1280;
    constexpr int windowHeight = 720;
    auto window = raylib::Window(windowWidth, windowHeight, "Friday Night Funkin'", FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);

    #if __APPLE__
    MacOSUtil::fixWindowColorSpace();
    #endif

    window.SetTargetFPS(GetMonitorRefreshRate(window.GetMonitor()) * 2);

    {
        auto iconOG = raylib::Image("assets/images/iconOG.png");
        window.SetIcon(iconOG);
    }

    auto audioDevice = raylib::AudioDevice();
    audioDevice.SetVolume(0.25f);

    auto game = engine::Game(new funkin::SongSelectState());

    while (!window.ShouldClose()) {

        if (IsKeyPressed(KEY_F11)) {
            window.ToggleFullscreen();
        }

        window.BeginDrawing();
        window.ClearBackground(BLACK);
        game.update(window.GetFrameTime());
        window.DrawFPS(10, 10);
        raylib::Text::Draw(funkin::CoolUtil::formatBytes(getCurrentRSS()) + " / " + funkin::CoolUtil::formatBytes(getPeakRSS()), 10, 30, 20, LIME);
        window.EndDrawing();
    }

    return 0;
}
