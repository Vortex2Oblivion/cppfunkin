#include <raylib-cpp.hpp>

#include "game.hpp"
#include "playstate.hpp"

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    raylib::Window window(1280, 720, "cppfunkin");

    InitAudioDevice();

    funkin::Game funkin = funkin::Game(new funkin::PlayState());

    while (!window.ShouldClose())
    {
        BeginDrawing();
        window.ClearBackground(BLACK);
        funkin.update(window.GetFrameTime());
        window.DrawFPS();
        EndDrawing();
    }

    CloseAudioDevice();
    return 0;
}