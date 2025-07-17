#include "raylib-cpp.hpp"
#include "conductor.cpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace std;

int main()
{
    ifstream f("assets/songs/parasitic/hard.json");
    json data = json::parse(f);
    int screenWidth = 1280;
    int screenHeight = 720;

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    InitAudioDevice();

    vector<raylib::Music *> tracks = {};
    tracks.push_back(new raylib::Music("assets/songs/parasitic/Inst.ogg"));
    tracks.push_back(new raylib::Music("assets/songs/parasitic/Voices.ogg"));

    conductor *_conductor = new conductor(tracks);
    _conductor->bpm = 235;

    tracks[0]->Play();
    tracks[1]->Play();
    SetTargetFPS(0);

    while (!window.ShouldClose())
    {
        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        window.DrawFPS();


        tracks[0]->Update();
        tracks[1]->Update();
        _conductor->update();

        EndDrawing();
    }

    CloseAudioDevice();

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}