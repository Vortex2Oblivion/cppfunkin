#include "raylib-cpp.hpp"
#include "conductor.cpp"
#include "note.cpp"
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

    
    Texture noteTexture = LoadTexture("assets/images/slungus.png");
    
    InitAudioDevice();
    
    vector<raylib::Music *> tracks = {};
    tracks.push_back(new raylib::Music("assets/songs/parasitic/Inst.ogg"));
    tracks.push_back(new raylib::Music("assets/songs/parasitic/Voices.ogg"));
    
    conductor *_conductor = new conductor(tracks);
    _conductor->bpm = data["song"]["bpm"];
    
    tracks[0]->Play();
    tracks[1]->Play();
    SetTargetFPS(0);
    
    vector<Color> colors = {PURPLE, BLUE, GREEN, RED};
    
    vector<note> notes = {};
    for(auto _note : data["song"]["notes"]){
        for(auto sectionNote : _note["sectionNotes"]){
            note __note = note(noteTexture, sectionNote[0], sectionNote[1], speed);
            __note.color = colors[(int)sectionNote[1]%4];
            notes.push_back(__note);
        }
    }


    while (!window.ShouldClose())
    {
        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        window.DrawFPS();


        tracks[0]->Update();
        tracks[1]->Update();
        _conductor->update();

        for(auto note : notes){
            note.time = _conductor->time;
            note.draw();
        }
        EndDrawing();
    }

    CloseAudioDevice();

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}