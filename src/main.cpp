#include <raylib-cpp.hpp>

#include "engine/game.hpp"
#include "engine/memorycounter.hpp"
#include "funkin/titlestate.hpp"

#include <iostream>
#include "funkin/coolutil.hpp"

#if __linux__
#include <gamemode_client.h>
#endif

#if __APPLE__
#include "engine/macos.hpp"
#endif

int main() {

    #if __linux__
    if (gamemode_request_start()) {
        std::cerr << "Failed to request gamemode start: " << gamemode_error_string() << std::endl;
    }
    #endif

    constexpr int windowWidth = 1280;
    constexpr int windowHeight = 720;
    auto window = raylib::Window(windowWidth, windowHeight, "Friday Night Funkin'", FLAG_WINDOW_HIGHDPI);

    #if __APPLE__
    MacOSUtil::fixWindowColorSpace();
    #endif

    window.SetTargetFPS(GetMonitorRefreshRate(raylib::Window::GetMonitor()) * 2);

    {
        auto iconOG = raylib::Image("assets/images/iconOG.png");
        window.SetIcon(iconOG);
        iconOG.Unload();
    }

    auto audioDevice = raylib::AudioDevice();
    audioDevice.SetVolume(0.25f);

    auto game = engine::Game(std::make_unique<funkin::TitleState>());

    while (!raylib::Window::ShouldClose()) {
        window.BeginDrawing();
        window.ClearBackground(BLACK);
        game.update(raylib::Window::GetFrameTime());
        raylib::Window::DrawFPS(10, 10);
        raylib::Text::Draw(funkin::CoolUtil::formatBytes(getCurrentRSS()) + " / " + funkin::CoolUtil::formatBytes(getPeakRSS()), 10, 30, 20, LIME);
        window.EndDrawing();
    }

    #if __linux__
    if (gamemode_request_end()) {
        std::cerr << "Failed to request gamemode end: " << gamemode_error_string() << std::endl;
    }
    #endif

    return 0;
}
