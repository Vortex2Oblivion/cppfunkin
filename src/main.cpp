#include <raylib-cpp.hpp>

#include "game.hpp"
#include "playstate.hpp"

int main()
{
    raylib::Window window(1280, 720, "cppfunkin");
    InitAudioDevice();
    window.SetTargetFPS(0);


    game *funkin = new game(new playstate());


    while (!window.ShouldClose())
    {
        BeginDrawing();
        window.ClearBackground(BLACK);
        funkin->update(window.GetFrameTime());
        window.DrawFPS();
        EndDrawing();
    }

    CloseAudioDevice();
    return 0;
}