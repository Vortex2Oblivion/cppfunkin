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

    double speed = data["song"]["speed"];

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    vector<raylib::Vector2> notes = {};

    for(auto note : data["song"]["notes"]){
        for(auto sectionNote : note["sectionNotes"]){
            notes.push_back(raylib::Vector2(sectionNote[0], sectionNote[1]));
        }
    }


    InitAudioDevice();

    vector<raylib::Music *> tracks = {};
    tracks.push_back(new raylib::Music("assets/songs/parasitic/Inst.ogg"));
    tracks.push_back(new raylib::Music("assets/songs/parasitic/Voices.ogg"));

    conductor *_conductor = new conductor(tracks);
    _conductor->bpm = data["song"]["bpm"];

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

        for(auto note : notes){
            DrawRectangle(note.y*100, -0.45 * ( _conductor->time * 1000 - note.x) * speed, 100, 100, RED);
        }
        EndDrawing();
    }

    CloseAudioDevice();

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}